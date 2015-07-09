input = """
% Total TBox Axioms: 49

Person(X) :- PhysicalPerson(X).
Transaction(X) :- Offer(X).
usesBroker(X, Y) :- tradesOnBehalfOf(Y, X).
tradesOnBehalfOf(Y, X) :- usesBroker(X, Y).
Company(X) :- hasStock(X, Y).
StockExchangeList(Y) :- isListedIn(X, Y).
Stock(Y) :- hasStock(X, Y).
Stock(X) :- belongsToCompany(X, Y).
Stock(Y) :- listsStock(X, Y).
isExecutedFor(X, Y) :- Transaction(X).
Transaction(X) :- isExecutedFor(X, Y).
LegalPerson(X) :- Company(X).
Address(Y) :- hasAddress(X, Y).
inverseofhasAddress(X, Y) :- hasAddress(Y, X).
hasAddress(Y, X) :- inverseofhasAddress(X, Y).
Person(X) :- hasAddress(X, Y).
StockExchangeMember(X) :- StockBroker(X).
FinantialInstrument(X) :- Stock(X).
FinantialInstrument(Y) :- involvesInstrument(X, Y).
StockTrader(X) :- Trader(X).
Trader(X) :- StockTrader(X).
Address(X) :- inverseofhasAddress(X, Y).
isExecutedBy(X, Y) :- Transaction(X).
Person(Y) :- inverseofhasAddress(X, Y).
StockBroker(X) :- Dealer(X).
involvesInstrument(X, Y) :- Transaction(X).
Stock(X) :- isListedIn(X, Y).
Company(Y) :- belongsToCompany(X, Y).
hasAddress(X, Y) :- Person(X).
Person(X) :- LegalPerson(X).
Transaction(X) :- isExecutedBy(X, Y).
StockBroker(X) :- StockTrader(X).
Dealer(X) :- Trader(X).
Trader(X) :- Dealer(X).
tradesOnBehalfOf(X, Y) :- StockBroker(X).
notLegalPerson(X) :- PhysicalPerson(X).
Transaction(X) :- involvesInstrument(X, Y).
isTradedIn(X, Y) :- involvesInstrument(Y, X).
involvesInstrument(Y, X) :- isTradedIn(X, Y).
Person(X) :- Investor(X).
Transaction(X) :- Acquisition(X).
isListedIn(X, Y) :- listsStock(Y, X).
listsStock(Y, X) :- isListedIn(X, Y).
StockExchangeMember(Y) :- isExecutedBy(X, Y).
belongsToCompany(X, Y) :- Stock(X).
Transaction(Y) :- isTradedIn(X, Y).
isListedIn(X, Y) :- Stock(X).
StockBroker(X) :- Trader(X).
Person(X) :- StockExchangeMember(X).
belongsToCompany(X, Y) :- hasStock(Y, X).
hasStock(Y, X) :- belongsToCompany(X, Y).
inverseofhasAddress(X, Y) :- Address(X).
Investor(Y) :- isExecutedFor(X, Y).
Q48(A) :- listsStock(A,B), hasStock(C,B).
Q48(A)?
"""
output = """
#rewriting: 2
"""
