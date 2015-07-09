input = """
% Total TBox Axioms: 74

degreeFrom(X, Y) :- doctoralDegreeFrom(X, Y).
Faculty(X) :- isPartOfUniversity(X, Y).
Professor(X) :- Dean(X).
University(Y) :- undergraduateDegreeFrom(X, Y).
Organization(X) :- University(X).
hasFaculty(X, Y) :- isPartOfUniversity(Y, X).
isPartOfUniversity(Y, X) :- hasFaculty(X, Y).
Person(X) :- Employee(X).
Professor(X) :- FullProfessor(X).
Organization(X) :- Program(X).
Person(Y) :- publicationAuthor(X, Y).
FacultyStaff(X) :- Professor(X).
University(Y) :- isPartOfUniversity(X, Y).
FacultyStaff(X) :- PostDoc(X).
Professor(X) :- AssociateProfessor(X).
Organization(Y) :- affiliatedOrganizationOf(X, Y).
Person(Y) :- member(X, Y).
memberOf(X, Y) :- worksFor(X, Y).
Employee(X) :- AdministrativeStaff(X).
Professor(X) :- AssistantProfessor(X).
University(X) :- hasAlumnus(X, Y).
Exam(X) :- BachelorExam(X).
aux_0(X,Y) :- Dean(X).
Employee(X) :- FacultyStaff(X).
Person(Y) :- affiliateOf(X, Y).
Person(X) :- doctoralDegreeFrom(X, Y).
Professor(Y) :- advisor(X, Y).
degreeFrom(X, Y) :- mastersDegreeFrom(X, Y).
Work(X) :- Course(X).
worksFor(X, Y) :- headOf(X, Y).
Person(X) :- Director(X).
Organization(X) :- member(X, Y).
FacultyStaff(X) :- Lecturer(X).
University(Y) :- degreeFrom(X, Y).
Professor(X) :- tenured(X, Y).
University(Y) :- doctoralDegreeFrom(X, Y).
member(X, Y) :- memberOf(Y, X).
memberOf(Y, X) :- member(X, Y).
Person(X) :- degreeFrom(X, Y).
Student(X) :- hasExamRecord(X, Y).
Organization(X) :- orgPublication(X, Y).
AdministrativeStaff(X) :- SystemsStaff(X).
Student(X) :- ResearchAssistant(X).
Faculty(Y) :- hasFaculty(X, Y).
ExamRecord(Y) :- hasExamRecord(X, Y).
Professor(X) :- Chair(X).
Person(X) :- undergraduateDegreeFrom(X, Y).
Person(X) :- mastersDegreeFrom(X, Y).
Organization(X) :- affiliatedOrganizationOf(X, Y).
degreeFrom(X, Y) :- undergraduateDegreeFrom(X, Y).
Person(X) :- Student(X).
Work(X) :- Career(X).
Professor(X) :- VisitingProfessor(X).
aux_1(X,Y) :- Director(X).
Course(Y) :- teachingAssistantOf(X, Y).
Organization(X) :- College(X).
Course(X) :- GraduateCourse(X).
degreeFrom(X, Y) :- hasAlumnus(Y, X).
hasAlumnus(Y, X) :- degreeFrom(X, Y).
aux_2(X,Y) :- Student(X).
Professor(X) :- ExDean(X).
Organization(X) :- affiliateOf(X, Y).
Work(X) :- ExamRecord(X).
aux_3(X,Y) :- Employee(X).
AdministrativeStaff(X) :- ClericalStaff(X).
Person(X) :- GraduateStudent(X).
Student(X) :- UndergraduateStudent(X).
Person(X) :- advisor(X, Y).
University(X) :- hasFaculty(X, Y).
Person(Y) :- hasAlumnus(X, Y).
Organization(X) :- Faculty(X).
FacultyStaff(X) :- teacherOf(X, Y).
Course(Y) :- teacherOf(X, Y).
aux_4(X,Y) :- GraduateStudent(X).
University(Y) :- mastersDegreeFrom(X, Y).
Work(X) :- Degree(X).
Work(X) :- Exam(X).
headOf(X,Y) :- aux_1(X,Y).
Program(Y) :- aux_1(X,Y).
takesCourse(X,Y) :- aux_2(X,Y).
Course(Y) :- aux_2(X,Y).
headOf(X,Y) :- aux_0(X,Y).
College(Y) :- aux_0(X,Y).
worksFor(X,Y) :- aux_3(X,Y).
Organization(Y) :- aux_3(X,Y).
takesCourse(X,Y) :- aux_4(X,Y).
GraduateCourse(Y) :- aux_4(X,Y).
Q21(A) :- doctoralDegreeFrom(A,B).
Q21(A)?
"""
output = """
#rewriting: 1
"""
