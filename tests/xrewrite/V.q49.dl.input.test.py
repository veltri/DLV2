input = """
% Total TBox Axioms: 222

Minister(X) :- Foreign_Minister(X).
Abstract_Notion(X) :- Idea(X).
Natural_Object(X) :- Commodity(X).
Artist(X) :- Composer(X).
VicodiOI(Y) :- related(X, Y).
Flavour(X) :- hasRole(X, Y).
Role(X) :- Symbol(X).
Writing(X) :- Journal(X).
Movement(X) :- Intellectual_Movement(X).
Leader(X) :- Religious_Leader(X).
Abstract_Notion(X) :- Artistic_Style(X).
Event(X) :- Election(X).
Object(X) :- Conceptual_Object(X).
related(X, Y) :- hasCategory(X, Y).
Organisation(X) :- Military_Organisation(X).
Social_Group(X) :- Dynasty(X).
Leader(X) :- Clerical_Leader(X).
Event(X) :- Treaty(X).
Geographical_Feature(X) :- Water(X).
Event(X) :- Cultural_Agreement(X).
Event(X) :- Technical_Scientific_Advance(X).
Role(Y) :- hasRole(X, Y).
Person_Role(X) :- Saint(X).
Artefact(X) :- Pollution(X).
Artefact(X) :- Armament(X).
Event(X) :- Public_Oration(X).
Person_Role(X) :- Professor(X).
Political_Organisation(X) :- International_Alliance(X).
Conceptual_Object(X) :- Ritual(X).
Conceptual_Object(X) :- Pastime(X).
Cultural_Organisation(X) :- Religious_Organisation(X).
Person_Role(X) :- Criminal(X).
VicodiOI(X) :- Category(X).
Vehicle(X) :- Ship(X).
Object(X) :- Artefact(X).
Event(X) :- War(X).
Creator(X) :- Author(X).
Flavour(X) :- Individual(X).
Settlement(X) :- Village(X).
Individual(X) :- Person(X).
Artefact(X) :- Clothing(X).
isRelationMemberOf(X, Y) :- isLocationContainerMemberOf(X, Y).
Person_Role(X) :- Leader(X).
Abstract_Notion(X) :- Ideology(X).
Natural_Object(X) :- Disease(X).
VicodiOI(X) :- related(X, Y).
Ideology(X) :- Secular_Ideology(X).
Political_Organisation(X) :- Governmental_Organisation(X).
related(X, Y) :- hasRole(X, Y).
Entertainer(X) :- Dancer(X).
Artist(X) :- Painter(X).
Artefact(X) :- Building(X).
Natural_Object(X) :- Animal(X).
Creator(X) :- Artist(X).
Creator(X) :- Publisher(X).
Symbol(X) :- National_Symbol(X).
Creator(X) :- Journalist(X).
hasRelationMember(X, Y) :- hasLocationPartMember(X, Y).
Location(Y) :- hasLocationContainerMember(X, Y).
Functionary(X) :- Minister(X).
Time_Dependent(X) :- isRelationMemberOf(X, Y).
Head_of_State(X) :- Sultan(X).
Location(X) :- Country(X).
Religious_Leader(X) :- Pope(X).
Person_Role(X) :- Sportsman(X).
Individual(X) :- Fictional_Person(X).
VicodiOI(X) :- Time_Dependent(X).
Artefact(X) :- Liturgical_Object(X).
Artefact(X) :- Writing(X).
Scientist(X) :- Geographer(X).
Work_of_Art(X) :- Piece_of_Music(X).
Social_Group(X) :- Movement(X).
Location_Part_Relation(Y) :- isLocationContainerMemberOf(X, Y).
Functionary(X) :- Jurist(X).
Organisation(X) :- Cultural_Organisation(X).
Person_Role(X) :- Discoverer(X).
Head_of_State(X) :- Prince(X).
Intellectual_Construct(X) :- Field_of_Knowledge(X).
Location(X) :- isLocationContainerMemberOf(X, Y).
Symbol(X) :- Political_Symbol(X).
Category(Y) :- hasCategory(X, Y).
Head_of_State(X) :- Emperor(X).
Organisation(X) :- International_Organisation(X).
Scientist(X) :- Psychologist(X).
Vehicle(X) :- Train(X).
Entertainer(X) :- Conductor(X).
Movement(X) :- Artistic_Movement(X).
Religious_Leader(X) :- Other_Religious_Leader(X).
Event(X) :- Economic_Process(X).
Economic_Organisation(X) :- Trade_Association(X).
Magnate(X) :- Business_Leader(X).
Event(X) :- Period(X).
Writing(X) :- Newspaper(X).
Ideology(X) :- Religious_Ideology(X).
Person_Role(X) :- Cleric(X).
Secular_Leader(X) :- Head_of_Government(X).
related(X, Y) :- hasRelationMember(X, Y).
Flavour(X) :- Social_Group(X).
Event(X) :- Trial(X).
Functionary(X) :- Politician(X).
Time(X) :- TemporalInterval(X).
Symbol(X) :- Religious_Symbol(X).
Object(X) :- Natural_Object(X).
Religious_Organisation(X) :- Religious_Community(X).
Geographical_Feature(X) :- Geographical_Region(X).
Location(X) :- Geographical_Feature(X).
Building(X) :- Abbey(X).
Conceptual_Object(X) :- Religious_Practice(X).
Abstract_Notion(X) :- Intellectual_Construct(X).
related(X, Y) :- isRelationMemberOf(X, Y).
Event(X) :- Meeting(X).
Abstract_Notion(X) :- Art_Form(X).
Abstract_Notion(X) :- Language(X).
Event(X) :- Non_Military_Conflict(X).
Artefact(X) :- Scientific_Instrument(X).
Creator(X) :- Engineer(X).
Location(X) :- Settlement(X).
Work_of_Art(X) :- Painting(X).
Time_Dependent(X) :- exists(X, Y).
Social_Group(X) :- Stereotype_Group(X).
Religious_Organisation(X) :- Religious_Order(X).
Life_Event(X) :- Illness(X).
Time_Dependent(Y) :- hasRelationMember(X, Y).
Building(X) :- Cathedral(X).
Organisation(X) :- Economic_Organisation(X).
Political_Organisation(X) :- League(X).
Movement(X) :- Religious_Movement(X).
Person_Role(X) :- Inventor(X).
Event(X) :- Crime(X).
Political_Organisation(X) :- Representative_Institution(X).
Flavour(X) :- Event(X).
Natural_Object(X) :- Environment(X).
Time_Dependent_Relation(X) :- Location_Part_Relation(X).
Religious_Leader(X) :- Ecclesiarch(X).
Flavour(X) :- Object(X).
Secular_Leader(X) :- Head_of_State(X).
Settlement(X) :- City(X).
Symbol(X) :- Economic_Symbol(X).
Event(X) :- Legislation(X).
Time_Dependent_Relation(X) :- hasRelationMember(X, Y).
Secular_Leader(X) :- Magnate(X).
Person_Role(X) :- Philanthropist(X).
Location_Part_Relation(X) :- hasLocationPartMember(X, Y).
Person_Role(X) :- Entertainer(X).
Discoverer(X) :- Astronaut(X).
Flavour(X) :- Location(X).
Work_of_Art(X) :- Sculpture(X).
Time(Y) :- exists(X, Y).
Person_Role(X) :- Scientist(X).
Conceptual_Object(X) :- Badge(X).
VicodiOI(X) :- Time(X).
Political_Organisation(X) :- Party(X).
Location(X) :- Political_Region(X).
Time_Dependent(X) :- hasCategory(X, Y).
Person_Role(X) :- Military_Person(X).
Location(X) :- isLocationPartMemberOf(X, Y).
Economic_Organisation(X) :- Economic_Enterprise(X).
Educational_Organisation(X) :- University(X).
Event(X) :- Fictional_Event(X).
Organisation(X) :- Management_Organisation(X).
Social_Group(X) :- Ethnic_Group(X).
Location_Part_Relation(Y) :- isLocationPartMemberOf(X, Y).
Event(X) :- Life_Event(X).
Flavour(X) :- Abstract_Notion(X).
Event(X) :- Battle(X).
Location(Y) :- hasLocationPartMember(X, Y).
Creator(X) :- Film_Maker(X).
Artefact(X) :- Structure(X).
Location_Part_Relation(X) :- hasLocationContainerMember(X, Y).
Event(X) :- Uprising(X).
Abstract_Notion(X) :- Measurable_Trend(X).
Time_Dependent(X) :- Time_Dependent_Relation(X).
Person_Role(X) :- Functionary(X).
Artefact(X) :- Work_of_Art(X).
isRelationMemberOf(X, Y) :- isLocationPartMemberOf(X, Y).
Building(X) :- Monastery(X).
Religious_Leader(X) :- Church_Reformer(X).
Organisation(X) :- Educational_Organisation(X).
Head_of_State(X) :- King(X).
Time_Dependent(X) :- Flavour(X).
Scientist(X) :- Philosopher(X).
Creator(X) :- Dramaturge(X).
Military_Organisation(X) :- Military_Unit(X).
Event(X) :- Disaster(X).
Management_Organisation(X) :- Board(X).
Artefact(X) :- Relic(X).
Event(X) :- Geographical_Discovery(X).
Event(X) :- Population_Movement(X).
Person_Role(X) :- Physician(X).
hasRelationMember(X, Y) :- hasLocationContainerMember(X, Y).
Functionary(X) :- Diplomat(X).
Writing(X) :- Book(X).
Economic_Organisation(X) :- Trades_Union(X).
Head_of_State(X) :- Queen(X).
Cultural_Organisation(X) :- Masonic_Lodge(X).
Scientist(X) :- Economist(X).
Person_Role(X) :- Creator(X).
Time_Dependent_Relation(Y) :- isRelationMemberOf(X, Y).
Organisation(X) :- Political_Organisation(X).
Secular_Leader(X) :- Trades_Unionist(X).
Time_Dependent(X) :- Role(X).
Person_Role(X) :- Theologian(X).
Natural_Object(X) :- Food(X).
Entertainer(X) :- Actor(X).
Artist(X) :- Sculptor(X).
Writing(X) :- Pamphlet(X).
Person_Role(X) :- Other_Religious_Person(X).
Time(X) :- FuzzyTemporalInterval(X).
Movement(X) :- Secular_Movement(X).
Leader(X) :- Secular_Leader(X).
Role(X) :- Person_Role(X).
related(X, Y) :- exists(X, Y).
Entertainer(X) :- Musician(X).
Artefact(X) :- Vehicle(X).
Event(X) :- Scandal(X).
Social_Group(X) :- Social_Stratum(X).
Creator(X) :- Architect(X).
Event(X) :- Period_in_Office(X).
Flavour(X) :- Organisation(X).
Building(X) :- Church(X).
Location(X) :- Intra_State_Group(X).
Geographical_Feature(X) :- Landmark(X).
Q49(A) :- Social_Group(A).
Q49(A)?
"""
output = """
#rewriting: 10
"""
