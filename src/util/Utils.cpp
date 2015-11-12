#include "Utils.h"
#include "Options.h"
#include "ErrorMessage.h"
#include "Trace.h"

#include <cstdlib>
#include <climits>
#include <sstream>
#include <cstring>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;
using namespace DLV2;

bool
Utils::parseLongInteger(
    const char* value,
    long int& result ) 
{
    char* err;
 
    int n=strtol(value, &err, 10);
    if ( *err )
        return false;
    
    result = n;
    return true;
}

bool
Utils::parseInteger(
    const char* value,
    int& result ) 
{
    char* err;
 
    int n=strtol(value, &err, 10);
    if ( *err || n < INT_MIN || n > INT_MAX )
        return false;
    
    result = n;
    return true;
}

bool 
Utils::isNumeric( 
    const char* pszInput, 
    int nNumberBase )
{
    istringstream iss( pszInput );
 
    if ( nNumberBase == 10 )
    {
        double dTestSink;
        iss >> dTestSink;
    }
    else if ( nNumberBase == 8 || nNumberBase == 16 )
    {
        int nTestSink;
        iss >> ( ( nNumberBase == 8 ) ? oct : hex ) >> nTestSink;
    }
    else
        return false;
 
    // Was any input successfully consumed/converted?
    if ( !iss )
        return false;
 
    // Was all the input successfully consumed/converted?
    return ( iss.rdbuf()->in_avail() == 0 );
}

const char*
Utils::getNegativeName(
    const string& name )
{
    char* temp;
    temp = new char[name.length()+2];
    temp[0] = '-';
    strcpy(temp+1,name.c_str());
    return temp;
}

void
Utils::systemCallTo(
    const char* executable,
    const std::string& input,
    char outputBuffer[],
    size_t outputBufferSize )
{
//    trace_msg( rewriting,3,"System call to " << executable );
//    trace_msg( rewriting,3,"The input is:\n" << input );

    unsigned READ_FD = 0;
    unsigned WRITE_FD = 1;

    unsigned TO_CHILD_PIPE = 0;
    unsigned FROM_CHILD_PIPE = 1;

    // The main process has to be split in order to execute the external program.

    // Create 2 pipes between the two processes:
    // - the former will be exploited to send the input to the program,
    // - the latter to read the result from the program.
    int pipesEnds[2][2];
    if ( pipe(pipesEnds[TO_CHILD_PIPE]) == -1
            || pipe (pipesEnds[FROM_CHILD_PIPE]) == -1 )
    {
        perror("pipe failed");
        ErrorMessage::errorGeneric("An error has occurred");
    }

    pid_t pid = fork();

    if( pid < 0 )
    {
        perror("fork failed");
        ErrorMessage::errorGeneric("An error has occurred");
    }

    if ( pid == 0 )
    {
        // This is the code the child runs

        // Close the useless pipes' ends
        close(pipesEnds[TO_CHILD_PIPE][WRITE_FD]);
        close(pipesEnds[FROM_CHILD_PIPE][READ_FD]);

        close(STDIN_FILENO);
        dup2(pipesEnds[TO_CHILD_PIPE][READ_FD], STDIN_FILENO);
        close(pipesEnds[TO_CHILD_PIPE][READ_FD]);

        close(STDOUT_FILENO);
        dup2(pipesEnds[FROM_CHILD_PIPE][WRITE_FD], STDOUT_FILENO);
        close(pipesEnds[FROM_CHILD_PIPE][WRITE_FD]);

        execl(executable,executable,(char*)0);

        // The call to function execv should substitute the child process
        // by the program argv[0], thus if the following code were executed
        // an error would have occurred.
        perror(executable);
        ErrorMessage::errorGeneric("An error has occurred");
    }
    else
    {
        // This is the code the parent runs

        // Close the useless pipes' ends
        close(pipesEnds[TO_CHILD_PIPE][READ_FD]);
        close(pipesEnds[FROM_CHILD_PIPE][WRITE_FD]);

        // Write to child’s stdin
//        trace_msg( rewriting,3,"The input is " << input );
        ssize_t code = write(pipesEnds[TO_CHILD_PIPE][WRITE_FD],input.c_str(),input.length());
        if( code < 0 )
        {
            perror(executable);
            ErrorMessage::errorGeneric("An error has occurred while sending child a message");
        }
        // The child process needs EOF to complete its work.
        close(pipesEnds[TO_CHILD_PIPE][WRITE_FD]);
        // The parent process needs the child process to compute the result before reading the answer.
        pid_t w;
        int status;
        w = wait(&status);
        if( w < 0 )
        {
            perror("wait");
            ErrorMessage::errorGeneric("An error has occurred while waiting for the child ending");
        }
        // Now read from the pipe
        int count = read(pipesEnds[FROM_CHILD_PIPE][READ_FD], outputBuffer, outputBufferSize*sizeof(char));
        if (count >= 0)
        {
            if( (count/sizeof(char)) < outputBufferSize )
                outputBuffer[(count/sizeof(char))] = '\0';
            else
                outputBuffer[outputBufferSize-1] = '\0';
            //                trace_msg( rewriting,3,"The output is " << outputBuffer );
        }
        else
            ErrorMessage::errorGeneric("IO Error");

        // Close the remaining end
        close(pipesEnds[FROM_CHILD_PIPE][READ_FD]);
    }
}
