#include "generate/column_string_names.h"


/* global variables
 *─────────────────────────────────────────────────────────────────────────── */
const struct Stub first_names[FIRST_NAMES_COUNT] = {
	{ .bytes = "Aaron",       .width = sizeof("Aaron")		- 1u },
	{ .bytes = "Abigail",     .width = sizeof("Abigail")		- 1u },
	{ .bytes = "Adam",        .width = sizeof("Adam")		- 1u },
	{ .bytes = "Alan",        .width = sizeof("Alan")		- 1u },
	{ .bytes = "Albert",      .width = sizeof("Albert")		- 1u },
	{ .bytes = "Alexander",   .width = sizeof("Alexander")		- 1u },
	{ .bytes = "Alice",       .width = sizeof("Alice")		- 1u },
	{ .bytes = "Amanda",      .width = sizeof("Amanda")		- 1u },
	{ .bytes = "Amber",       .width = sizeof("Amber")		- 1u },
	{ .bytes = "Amy",         .width = sizeof("Amy")		- 1u },
	{ .bytes = "Andrea",      .width = sizeof("Andrea")		- 1u },
	{ .bytes = "Andrew",      .width = sizeof("Andrew")		- 1u },
	{ .bytes = "Angela",      .width = sizeof("Angela")		- 1u },
	{ .bytes = "Ann",         .width = sizeof("Ann")		- 1u },
	{ .bytes = "Anna",        .width = sizeof("Anna")		- 1u },
	{ .bytes = "Anthony",     .width = sizeof("Anthony")		- 1u },
	{ .bytes = "Arthur",      .width = sizeof("Arthur")		- 1u },
	{ .bytes = "Ashley",      .width = sizeof("Ashley")		- 1u },
	{ .bytes = "Austin",      .width = sizeof("Austin")		- 1u },
	{ .bytes = "Barbara",     .width = sizeof("Barbara")		- 1u },
	{ .bytes = "Benjamin",    .width = sizeof("Benjamin")		- 1u },
	{ .bytes = "Betty",       .width = sizeof("Betty")		- 1u },
	{ .bytes = "Beverly",     .width = sizeof("Beverly")		- 1u },
	{ .bytes = "Billy",       .width = sizeof("Billy")		- 1u },
	{ .bytes = "Bobby",       .width = sizeof("Bobby")		- 1u },
	{ .bytes = "Brandon",     .width = sizeof("Brandon")		- 1u },
	{ .bytes = "Brenda",      .width = sizeof("Brenda")		- 1u },
	{ .bytes = "Brian",       .width = sizeof("Brian")		- 1u },
	{ .bytes = "Brittany",    .width = sizeof("Brittany")		- 1u },
	{ .bytes = "Bruce",       .width = sizeof("Bruce")		- 1u },
	{ .bytes = "Bryan",       .width = sizeof("Bryan")		- 1u },
	{ .bytes = "Carl",        .width = sizeof("Carl")		- 1u },
	{ .bytes = "Carol",       .width = sizeof("Carol")		- 1u },
	{ .bytes = "Carolyn",     .width = sizeof("Carolyn")		- 1u },
	{ .bytes = "Catherine",   .width = sizeof("Catherine")		- 1u },
	{ .bytes = "Charles",     .width = sizeof("Charles")		- 1u },
	{ .bytes = "Cheryl",      .width = sizeof("Cheryl")		- 1u },
	{ .bytes = "Christian",   .width = sizeof("Christian")		- 1u },
	{ .bytes = "Christina",   .width = sizeof("Christina")		- 1u },
	{ .bytes = "Christine",   .width = sizeof("Christine")		- 1u },
	{ .bytes = "Christopher", .width = sizeof("Christopher")	- 1u },
	{ .bytes = "Cynthia",     .width = sizeof("Cynthia")		- 1u },
	{ .bytes = "Daniel",      .width = sizeof("Daniel")		- 1u },
	{ .bytes = "Danielle",    .width = sizeof("Danielle")		- 1u },
	{ .bytes = "David",       .width = sizeof("David")		- 1u },
	{ .bytes = "Deborah",     .width = sizeof("Deborah")		- 1u },
	{ .bytes = "Debra",       .width = sizeof("Debra")		- 1u },
	{ .bytes = "Denise",      .width = sizeof("Denise")		- 1u },
	{ .bytes = "Dennis",      .width = sizeof("Dennis")		- 1u },
	{ .bytes = "Diana",       .width = sizeof("Diana")		- 1u },
	{ .bytes = "Diane",       .width = sizeof("Diane")		- 1u },
	{ .bytes = "Donald",      .width = sizeof("Donald")		- 1u },
	{ .bytes = "Donna",       .width = sizeof("Donna")		- 1u },
	{ .bytes = "Doris",       .width = sizeof("Doris")		- 1u },
	{ .bytes = "Dorothy",     .width = sizeof("Dorothy")		- 1u },
	{ .bytes = "Douglas",     .width = sizeof("Douglas")		- 1u },
	{ .bytes = "Dylan",       .width = sizeof("Dylan")		- 1u },
	{ .bytes = "Edward",      .width = sizeof("Edward")		- 1u },
	{ .bytes = "Elizabeth",   .width = sizeof("Elizabeth")		- 1u },
	{ .bytes = "Emily",       .width = sizeof("Emily")		- 1u },
	{ .bytes = "Emma",        .width = sizeof("Emma")		- 1u },
	{ .bytes = "Eric",        .width = sizeof("Eric")		- 1u },
	{ .bytes = "Ethan",       .width = sizeof("Ethan")		- 1u },
	{ .bytes = "Eugene",      .width = sizeof("Eugene")		- 1u },
	{ .bytes = "Evelyn",      .width = sizeof("Evelyn")		- 1u },
	{ .bytes = "Frances",     .width = sizeof("Frances")		- 1u },
	{ .bytes = "Frank",       .width = sizeof("Frank")		- 1u },
	{ .bytes = "Gabriel",     .width = sizeof("Gabriel")		- 1u },
	{ .bytes = "Gary",        .width = sizeof("Gary")		- 1u },
	{ .bytes = "George",      .width = sizeof("George")		- 1u },
	{ .bytes = "Gerald",      .width = sizeof("Gerald")		- 1u },
	{ .bytes = "Gloria",      .width = sizeof("Gloria")		- 1u },
	{ .bytes = "Grace",       .width = sizeof("Grace")		- 1u },
	{ .bytes = "Gregory",     .width = sizeof("Gregory")		- 1u },
	{ .bytes = "Hannah",      .width = sizeof("Hannah")		- 1u },
	{ .bytes = "Harold",      .width = sizeof("Harold")		- 1u },
	{ .bytes = "Harry",       .width = sizeof("Harry")		- 1u },
	{ .bytes = "Heather",     .width = sizeof("Heather")		- 1u },
	{ .bytes = "Helen",       .width = sizeof("Helen")		- 1u },
	{ .bytes = "Henry",       .width = sizeof("Henry")		- 1u },
	{ .bytes = "Howard",      .width = sizeof("Howard")		- 1u },
	{ .bytes = "Jack",        .width = sizeof("Jack")		- 1u },
	{ .bytes = "Jacob",       .width = sizeof("Jacob")		- 1u },
	{ .bytes = "Jacqueline",  .width = sizeof("Jacqueline")		- 1u },
	{ .bytes = "James",       .width = sizeof("James")		- 1u },
	{ .bytes = "Jane",        .width = sizeof("Jane")		- 1u },
	{ .bytes = "Janet",       .width = sizeof("Janet")		- 1u },
	{ .bytes = "Janice",      .width = sizeof("Janice")		- 1u },
	{ .bytes = "Jason",       .width = sizeof("Jason")		- 1u },
	{ .bytes = "Jean",        .width = sizeof("Jean")		- 1u },
	{ .bytes = "Jeffrey",     .width = sizeof("Jeffrey")		- 1u },
	{ .bytes = "Jennifer",    .width = sizeof("Jennifer")		- 1u },
	{ .bytes = "Jeremy",      .width = sizeof("Jeremy")		- 1u },
	{ .bytes = "Jerry",       .width = sizeof("Jerry")		- 1u },
	{ .bytes = "Jesse",       .width = sizeof("Jesse")		- 1u },
	{ .bytes = "Jessica",     .width = sizeof("Jessica")		- 1u },
	{ .bytes = "Joan",        .width = sizeof("Joan")		- 1u },
	{ .bytes = "Joe",         .width = sizeof("Joe")		- 1u },
	{ .bytes = "John",        .width = sizeof("John")		- 1u },
	{ .bytes = "Johnny",      .width = sizeof("Johnny")		- 1u },
	{ .bytes = "Jonathan",    .width = sizeof("Jonathan")		- 1u },
	{ .bytes = "Jordan",      .width = sizeof("Jordan")		- 1u },
	{ .bytes = "Jose",        .width = sizeof("Jose")		- 1u },
	{ .bytes = "Joseph",      .width = sizeof("Joseph")		- 1u },
	{ .bytes = "Joshua",      .width = sizeof("Joshua")		- 1u },
	{ .bytes = "Joyce",       .width = sizeof("Joyce")		- 1u },
	{ .bytes = "Juan",        .width = sizeof("Juan")		- 1u },
	{ .bytes = "Judith",      .width = sizeof("Judith")		- 1u },
	{ .bytes = "Judy",        .width = sizeof("Judy")		- 1u },
	{ .bytes = "Julia",       .width = sizeof("Julia")		- 1u },
	{ .bytes = "Julie",       .width = sizeof("Julie")		- 1u },
	{ .bytes = "Justin",      .width = sizeof("Justin")		- 1u },
	{ .bytes = "Karen",       .width = sizeof("Karen")		- 1u },
	{ .bytes = "Katherine",   .width = sizeof("Katherine")		- 1u },
	{ .bytes = "Kathleen",    .width = sizeof("Kathleen")		- 1u },
	{ .bytes = "Kathryn",     .width = sizeof("Kathryn")		- 1u },
	{ .bytes = "Kathy",       .width = sizeof("Kathy")		- 1u },
	{ .bytes = "Keith",       .width = sizeof("Keith")		- 1u },
	{ .bytes = "Kelly",       .width = sizeof("Kelly")		- 1u },
	{ .bytes = "Kenneth",     .width = sizeof("Kenneth")		- 1u },
	{ .bytes = "Kevin",       .width = sizeof("Kevin")		- 1u },
	{ .bytes = "Kimberly",    .width = sizeof("Kimberly")		- 1u },
	{ .bytes = "Kyle",        .width = sizeof("Kyle")		- 1u },
	{ .bytes = "Larry",       .width = sizeof("Larry")		- 1u },
	{ .bytes = "Laura",       .width = sizeof("Laura")		- 1u },
	{ .bytes = "Lauren",      .width = sizeof("Lauren")		- 1u },
	{ .bytes = "Lawrence",    .width = sizeof("Lawrence")		- 1u },
	{ .bytes = "Linda",       .width = sizeof("Linda")		- 1u },
	{ .bytes = "Lisa",        .width = sizeof("Lisa")		- 1u },
	{ .bytes = "Lori",        .width = sizeof("Lori")		- 1u },
	{ .bytes = "Louis",       .width = sizeof("Louis")		- 1u },
	{ .bytes = "Madison",     .width = sizeof("Madison")		- 1u },
	{ .bytes = "Margaret",    .width = sizeof("Margaret")		- 1u },
	{ .bytes = "Maria",       .width = sizeof("Maria")		- 1u },
	{ .bytes = "Marie",       .width = sizeof("Marie")		- 1u },
	{ .bytes = "Marilyn",     .width = sizeof("Marilyn")		- 1u },
	{ .bytes = "Mark",        .width = sizeof("Mark")		- 1u },
	{ .bytes = "Martha",      .width = sizeof("Martha")		- 1u },
	{ .bytes = "Mary",        .width = sizeof("Mary")		- 1u },
	{ .bytes = "Matthew",     .width = sizeof("Matthew")		- 1u },
	{ .bytes = "Megan",       .width = sizeof("Megan")		- 1u },
	{ .bytes = "Melissa",     .width = sizeof("Melissa")		- 1u },
	{ .bytes = "Michael",     .width = sizeof("Michael")		- 1u },
	{ .bytes = "Michelle",    .width = sizeof("Michelle")		- 1u },
	{ .bytes = "Mildred",     .width = sizeof("Mildred")		- 1u },
	{ .bytes = "Nancy",       .width = sizeof("Nancy")		- 1u },
	{ .bytes = "Natalie",     .width = sizeof("Natalie")		- 1u },
	{ .bytes = "Nathan",      .width = sizeof("Nathan")		- 1u },
	{ .bytes = "Nicholas",    .width = sizeof("Nicholas")		- 1u },
	{ .bytes = "Nicole",      .width = sizeof("Nicole")		- 1u },
	{ .bytes = "Noah",        .width = sizeof("Noah")		- 1u },
	{ .bytes = "Olivia",      .width = sizeof("Olivia")		- 1u },
	{ .bytes = "Pamela",      .width = sizeof("Pamela")		- 1u },
	{ .bytes = "Patricia",    .width = sizeof("Patricia")		- 1u },
	{ .bytes = "Patrick",     .width = sizeof("Patrick")		- 1u },
	{ .bytes = "Paul",        .width = sizeof("Paul")		- 1u },
	{ .bytes = "Peter",       .width = sizeof("Peter")		- 1u },
	{ .bytes = "Philip",      .width = sizeof("Philip")		- 1u },
	{ .bytes = "Rachel",      .width = sizeof("Rachel")		- 1u },
	{ .bytes = "Ralph",       .width = sizeof("Ralph")		- 1u },
	{ .bytes = "Randy",       .width = sizeof("Randy")		- 1u },
	{ .bytes = "Raymond",     .width = sizeof("Raymond")		- 1u },
	{ .bytes = "Rebecca",     .width = sizeof("Rebecca")		- 1u },
	{ .bytes = "Richard",     .width = sizeof("Richard")		- 1u },
	{ .bytes = "Robert",      .width = sizeof("Robert")		- 1u },
	{ .bytes = "Roger",       .width = sizeof("Roger")		- 1u },
	{ .bytes = "Ronald",      .width = sizeof("Ronald")		- 1u },
	{ .bytes = "Rose",        .width = sizeof("Rose")		- 1u },
	{ .bytes = "Roy",         .width = sizeof("Roy")		- 1u },
	{ .bytes = "Russell",     .width = sizeof("Russell")		- 1u },
	{ .bytes = "Ruth",        .width = sizeof("Ruth")		- 1u },
	{ .bytes = "Ryan",        .width = sizeof("Ryan")		- 1u },
	{ .bytes = "Samantha",    .width = sizeof("Samantha")		- 1u },
	{ .bytes = "Samuel",      .width = sizeof("Samuel")		- 1u },
	{ .bytes = "Sandra",      .width = sizeof("Sandra")		- 1u },
	{ .bytes = "Sara",        .width = sizeof("Sara")		- 1u },
	{ .bytes = "Sarah",       .width = sizeof("Sarah")		- 1u },
	{ .bytes = "Scott",       .width = sizeof("Scott")		- 1u },
	{ .bytes = "Sean",        .width = sizeof("Sean")		- 1u },
	{ .bytes = "Sharon",      .width = sizeof("Sharon")		- 1u },
	{ .bytes = "Shirley",     .width = sizeof("Shirley")		- 1u },
	{ .bytes = "Stephanie",   .width = sizeof("Stephanie")		- 1u },
	{ .bytes = "Stephen",     .width = sizeof("Stephen")		- 1u },
	{ .bytes = "Steven",      .width = sizeof("Steven")		- 1u },
	{ .bytes = "Susan",       .width = sizeof("Susan")		- 1u },
	{ .bytes = "Teresa",      .width = sizeof("Teresa")		- 1u },
	{ .bytes = "Terry",       .width = sizeof("Terry")		- 1u },
	{ .bytes = "Theresa",     .width = sizeof("Theresa")		- 1u },
	{ .bytes = "Thomas",      .width = sizeof("Thomas")		- 1u },
	{ .bytes = "Tiffany",     .width = sizeof("Tiffany")		- 1u },
	{ .bytes = "Timothy",     .width = sizeof("Timothy")		- 1u },
	{ .bytes = "Tyler",       .width = sizeof("Tyler")		- 1u },
	{ .bytes = "Victoria",    .width = sizeof("Victoria")		- 1u },
	{ .bytes = "Vincent",     .width = sizeof("Vincent")		- 1u },
	{ .bytes = "Virginia",    .width = sizeof("Virginia")		- 1u },
	{ .bytes = "Walter",      .width = sizeof("Walter")		- 1u },
	{ .bytes = "Wayne",       .width = sizeof("Wayne")		- 1u },
	{ .bytes = "William",     .width = sizeof("William")		- 1u },
	{ .bytes = "Willie",      .width = sizeof("Willie")		- 1u },
	{ .bytes = "Zachary",     .width = sizeof("Zachary")		- 1u }
};

const struct Stub last_names[LAST_NAMES_COUNT] = {
	{ .bytes = "Adams",     .width = sizeof("Adams")		- 1u },
	{ .bytes = "Alexander", .width = sizeof("Alexander")		- 1u },
	{ .bytes = "Allen",     .width = sizeof("Allen")		- 1u },
	{ .bytes = "Anderson",  .width = sizeof("Anderson")		- 1u },
	{ .bytes = "Andrews",   .width = sizeof("Andrews")		- 1u },
	{ .bytes = "Armstrong", .width = sizeof("Armstrong")		- 1u },
	{ .bytes = "Arnold",    .width = sizeof("Arnold")		- 1u },
	{ .bytes = "Austin",    .width = sizeof("Austin")		- 1u },
	{ .bytes = "Bailey",    .width = sizeof("Bailey")		- 1u },
	{ .bytes = "Baker",     .width = sizeof("Baker")		- 1u },
	{ .bytes = "Barnes",    .width = sizeof("Barnes")		- 1u },
	{ .bytes = "Bell",      .width = sizeof("Bell")			- 1u },
	{ .bytes = "Bennett",   .width = sizeof("Bennett")		- 1u },
	{ .bytes = "Berry",     .width = sizeof("Berry")		- 1u },
	{ .bytes = "Black",     .width = sizeof("Black")		- 1u },
	{ .bytes = "Boyd",      .width = sizeof("Boyd")			- 1u },
	{ .bytes = "Bradley",   .width = sizeof("Bradley")		- 1u },
	{ .bytes = "Brooks",    .width = sizeof("Brooks")		- 1u },
	{ .bytes = "Brown",     .width = sizeof("Brown")		- 1u },
	{ .bytes = "Bryant",    .width = sizeof("Bryant")		- 1u },
	{ .bytes = "Burns",     .width = sizeof("Burns")		- 1u },
	{ .bytes = "Butler",    .width = sizeof("Butler")		- 1u },
	{ .bytes = "Campbell",  .width = sizeof("Campbell")		- 1u },
	{ .bytes = "Carpenter", .width = sizeof("Carpenter")		- 1u },
	{ .bytes = "Carroll",   .width = sizeof("Carroll")		- 1u },
	{ .bytes = "Carter",    .width = sizeof("Carter")		- 1u },
	{ .bytes = "Chavez",    .width = sizeof("Chavez")		- 1u },
	{ .bytes = "Clark",     .width = sizeof("Clark")		- 1u },
	{ .bytes = "Cole",      .width = sizeof("Cole")			- 1u },
	{ .bytes = "Coleman",   .width = sizeof("Coleman")		- 1u },
	{ .bytes = "Collins",   .width = sizeof("Collins")		- 1u },
	{ .bytes = "Cook",      .width = sizeof("Cook")			- 1u },
	{ .bytes = "Cooper",    .width = sizeof("Cooper")		- 1u },
	{ .bytes = "Cox",       .width = sizeof("Cox")			- 1u },
	{ .bytes = "Crawford",  .width = sizeof("Crawford")		- 1u },
	{ .bytes = "Cruz",      .width = sizeof("Cruz")			- 1u },
	{ .bytes = "Cunningham",.width = sizeof("Cunningham")		- 1u },
	{ .bytes = "Daniels",   .width = sizeof("Daniels")		- 1u },
	{ .bytes = "Davis",     .width = sizeof("Davis")		- 1u },
	{ .bytes = "Diaz",      .width = sizeof("Diaz")			- 1u },
	{ .bytes = "Dixon",     .width = sizeof("Dixon")		- 1u },
	{ .bytes = "Duncan",    .width = sizeof("Duncan")		- 1u },
	{ .bytes = "Dunn",      .width = sizeof("Dunn")			- 1u },
	{ .bytes = "Edwards",   .width = sizeof("Edwards")		- 1u },
	{ .bytes = "Elliott",   .width = sizeof("Elliott")		- 1u },
	{ .bytes = "Ellis",     .width = sizeof("Ellis")		- 1u },
	{ .bytes = "Evans",     .width = sizeof("Evans")		- 1u },
	{ .bytes = "Ferguson",  .width = sizeof("Ferguson")		- 1u },
	{ .bytes = "Fisher",    .width = sizeof("Fisher")		- 1u },
	{ .bytes = "Flores",    .width = sizeof("Flores")		- 1u },
	{ .bytes = "Ford",      .width = sizeof("Ford")			- 1u },
	{ .bytes = "Foster",    .width = sizeof("Foster")		- 1u },
	{ .bytes = "Fox",       .width = sizeof("Fox")			- 1u },
	{ .bytes = "Franklin",  .width = sizeof("Franklin")		- 1u },
	{ .bytes = "Freeman",   .width = sizeof("Freeman")		- 1u },
	{ .bytes = "Garcia",    .width = sizeof("Garcia")		- 1u },
	{ .bytes = "Gardner",   .width = sizeof("Gardner")		- 1u },
	{ .bytes = "Gibson",    .width = sizeof("Gibson")		- 1u },
	{ .bytes = "Gomez",     .width = sizeof("Gomez")		- 1u },
	{ .bytes = "Gonzales",  .width = sizeof("Gonzales")		- 1u },
	{ .bytes = "Gonzalez",  .width = sizeof("Gonzalez")		- 1u },
	{ .bytes = "Gordon",    .width = sizeof("Gordon")		- 1u },
	{ .bytes = "Graham",    .width = sizeof("Graham")		- 1u },
	{ .bytes = "Grant",     .width = sizeof("Grant")		- 1u },
	{ .bytes = "Gray",      .width = sizeof("Gray")			- 1u },
	{ .bytes = "Green",     .width = sizeof("Green")		- 1u },
	{ .bytes = "Greene",    .width = sizeof("Greene")		- 1u },
	{ .bytes = "Griffin",   .width = sizeof("Griffin")		- 1u },
	{ .bytes = "Hall",      .width = sizeof("Hall")			- 1u },
	{ .bytes = "Hamilton",  .width = sizeof("Hamilton")		- 1u },
	{ .bytes = "Harper",    .width = sizeof("Harper")		- 1u },
	{ .bytes = "Harris",    .width = sizeof("Harris")		- 1u },
	{ .bytes = "Harrison",  .width = sizeof("Harrison")		- 1u },
	{ .bytes = "Hart",      .width = sizeof("Hart")			- 1u },
	{ .bytes = "Hawkins",   .width = sizeof("Hawkins")		- 1u },
	{ .bytes = "Hayes",     .width = sizeof("Hayes")		- 1u },
	{ .bytes = "Henderson", .width = sizeof("Henderson")		- 1u },
	{ .bytes = "Henry",     .width = sizeof("Henry")		- 1u },
	{ .bytes = "Hernandez", .width = sizeof("Hernandez")		- 1u },
	{ .bytes = "Hicks",     .width = sizeof("Hicks")		- 1u },
	{ .bytes = "Hill",      .width = sizeof("Hill")			- 1u },
	{ .bytes = "Holmes",    .width = sizeof("Holmes")		- 1u },
	{ .bytes = "Howard",    .width = sizeof("Howard")		- 1u },
	{ .bytes = "Hudson",    .width = sizeof("Hudson")		- 1u },
	{ .bytes = "Hughes",    .width = sizeof("Hughes")		- 1u },
	{ .bytes = "Hunt",      .width = sizeof("Hunt")			- 1u },
	{ .bytes = "Hunter",    .width = sizeof("Hunter")		- 1u },
	{ .bytes = "Jackson",   .width = sizeof("Jackson")		- 1u },
	{ .bytes = "James",     .width = sizeof("James")		- 1u },
	{ .bytes = "Jenkins",   .width = sizeof("Jenkins")		- 1u },
	{ .bytes = "Johnson",   .width = sizeof("Johnson")		- 1u },
	{ .bytes = "Jones",     .width = sizeof("Jones")		- 1u },
	{ .bytes = "Jordan",    .width = sizeof("Jordan")		- 1u },
	{ .bytes = "Kelley",    .width = sizeof("Kelley")		- 1u },
	{ .bytes = "Kelly",     .width = sizeof("Kelly")		- 1u },
	{ .bytes = "Kennedy",   .width = sizeof("Kennedy")		- 1u },
	{ .bytes = "King",      .width = sizeof("King")			- 1u },
	{ .bytes = "Knight",    .width = sizeof("Knight")		- 1u },
	{ .bytes = "Lane",      .width = sizeof("Lane")			- 1u },
	{ .bytes = "Lawrence",  .width = sizeof("Lawrence")		- 1u },
	{ .bytes = "Lawson",    .width = sizeof("Lawson")		- 1u },
	{ .bytes = "Lee",       .width = sizeof("Lee")			- 1u },
	{ .bytes = "Lewis",     .width = sizeof("Lewis")		- 1u },
	{ .bytes = "Long",      .width = sizeof("Long")			- 1u },
	{ .bytes = "Lopez",     .width = sizeof("Lopez")		- 1u },
	{ .bytes = "Marshall",  .width = sizeof("Marshall")		- 1u },
	{ .bytes = "Martin",    .width = sizeof("Martin")		- 1u },
	{ .bytes = "Martinez",  .width = sizeof("Martinez")		- 1u },
	{ .bytes = "Mason",     .width = sizeof("Mason")		- 1u },
	{ .bytes = "Matthews",  .width = sizeof("Matthews")		- 1u },
	{ .bytes = "Mcdonald",  .width = sizeof("Mcdonald")		- 1u },
	{ .bytes = "Miller",    .width = sizeof("Miller")		- 1u },
	{ .bytes = "Mills",     .width = sizeof("Mills")		- 1u },
	{ .bytes = "Mitchell",  .width = sizeof("Mitchell")		- 1u },
	{ .bytes = "Moore",     .width = sizeof("Moore")		- 1u },
	{ .bytes = "Morales",   .width = sizeof("Morales")		- 1u },
	{ .bytes = "Morgan",    .width = sizeof("Morgan")		- 1u },
	{ .bytes = "Morris",    .width = sizeof("Morris")		- 1u },
	{ .bytes = "Murphy",    .width = sizeof("Murphy")		- 1u },
	{ .bytes = "Murray",    .width = sizeof("Murray")		- 1u },
	{ .bytes = "Myers",     .width = sizeof("Myers")		- 1u },
	{ .bytes = "Nelson",    .width = sizeof("Nelson")		- 1u },
	{ .bytes = "Nichols",   .width = sizeof("Nichols")		- 1u },
	{ .bytes = "Olson",     .width = sizeof("Olson")		- 1u },
	{ .bytes = "Ortiz",     .width = sizeof("Ortiz")		- 1u },
	{ .bytes = "Owens",     .width = sizeof("Owens")		- 1u },
	{ .bytes = "Palmer",    .width = sizeof("Palmer")		- 1u },
	{ .bytes = "Parker",    .width = sizeof("Parker")		- 1u },
	{ .bytes = "Patterson", .width = sizeof("Patterson")		- 1u },
	{ .bytes = "Payne",     .width = sizeof("Payne")		- 1u },
	{ .bytes = "Perez",     .width = sizeof("Perez")		- 1u },
	{ .bytes = "Perkins",   .width = sizeof("Perkins")		- 1u },
	{ .bytes = "Perry",     .width = sizeof("Perry")		- 1u },
	{ .bytes = "Peters",    .width = sizeof("Peters")		- 1u },
	{ .bytes = "Peterson",  .width = sizeof("Peterson")		- 1u },
	{ .bytes = "Phillips",  .width = sizeof("Phillips")		- 1u },
	{ .bytes = "Pierce",    .width = sizeof("Pierce")		- 1u },
	{ .bytes = "Porter",    .width = sizeof("Porter")		- 1u },
	{ .bytes = "Powell",    .width = sizeof("Powell")		- 1u },
	{ .bytes = "Price",     .width = sizeof("Price")		- 1u },
	{ .bytes = "Ramirez",   .width = sizeof("Ramirez")		- 1u },
	{ .bytes = "Ramos",     .width = sizeof("Ramos")		- 1u },
	{ .bytes = "Ray",       .width = sizeof("Ray")			- 1u },
	{ .bytes = "Reed",      .width = sizeof("Reed")			- 1u },
	{ .bytes = "Reyes",     .width = sizeof("Reyes")		- 1u },
	{ .bytes = "Reynolds",  .width = sizeof("Reynolds")		- 1u },
	{ .bytes = "Rice",      .width = sizeof("Rice")			- 1u },
	{ .bytes = "Richardson",.width = sizeof("Richardson")		- 1u },
	{ .bytes = "Riley",     .width = sizeof("Riley")		- 1u },
	{ .bytes = "Rivera",    .width = sizeof("Rivera")		- 1u },
	{ .bytes = "Roberts",   .width = sizeof("Roberts")		- 1u },
	{ .bytes = "Robertson", .width = sizeof("Robertson")		- 1u },
	{ .bytes = "Robinson",  .width = sizeof("Robinson")		- 1u },
	{ .bytes = "Rodriguez", .width = sizeof("Rodriguez")		- 1u },
	{ .bytes = "Rogers",    .width = sizeof("Rogers")		- 1u },
	{ .bytes = "Rose",      .width = sizeof("Rose")			- 1u },
	{ .bytes = "Ross",      .width = sizeof("Ross")			- 1u },
	{ .bytes = "Ruiz",      .width = sizeof("Ruiz")			- 1u },
	{ .bytes = "Russell",   .width = sizeof("Russell")		- 1u },
	{ .bytes = "Sanchez",   .width = sizeof("Sanchez")		- 1u },
	{ .bytes = "Sanders",   .width = sizeof("Sanders")		- 1u },
	{ .bytes = "Scott",     .width = sizeof("Scott")		- 1u },
	{ .bytes = "Shaw",      .width = sizeof("Shaw")			- 1u },
	{ .bytes = "Simmons",   .width = sizeof("Simmons")		- 1u },
	{ .bytes = "Simpson",   .width = sizeof("Simpson")		- 1u },
	{ .bytes = "Sims",      .width = sizeof("Sims")			- 1u },
	{ .bytes = "Smith",     .width = sizeof("Smith")		- 1u },
	{ .bytes = "Snyder",    .width = sizeof("Snyder")		- 1u },
	{ .bytes = "Spencer",   .width = sizeof("Spencer")		- 1u },
	{ .bytes = "Stephens",  .width = sizeof("Stephens")		- 1u },
	{ .bytes = "Stevens",   .width = sizeof("Stevens")		- 1u },
	{ .bytes = "Stewart",   .width = sizeof("Stewart")		- 1u },
	{ .bytes = "Stone",     .width = sizeof("Stone")		- 1u },
	{ .bytes = "Sullivan",  .width = sizeof("Sullivan")		- 1u },
	{ .bytes = "Taylor",    .width = sizeof("Taylor")		- 1u },
	{ .bytes = "Thomas",    .width = sizeof("Thomas")		- 1u },
	{ .bytes = "Thompson",  .width = sizeof("Thompson")		- 1u },
	{ .bytes = "Torres",    .width = sizeof("Torres")		- 1u },
	{ .bytes = "Tucker",    .width = sizeof("Tucker")		- 1u },
	{ .bytes = "Turner",    .width = sizeof("Turner")		- 1u },
	{ .bytes = "Wagner",    .width = sizeof("Wagner")		- 1u },
	{ .bytes = "Walker",    .width = sizeof("Walker")		- 1u },
	{ .bytes = "Wallace",   .width = sizeof("Wallace")		- 1u },
	{ .bytes = "Ward",      .width = sizeof("Ward")			- 1u },
	{ .bytes = "Warren",    .width = sizeof("Warren")		- 1u },
	{ .bytes = "Washington",.width = sizeof("Washington")		- 1u },
	{ .bytes = "Watkins",   .width = sizeof("Watkins")		- 1u },
	{ .bytes = "Watson",    .width = sizeof("Watson")		- 1u },
	{ .bytes = "Weaver",    .width = sizeof("Weaver")		- 1u },
	{ .bytes = "Webb",      .width = sizeof("Webb")			- 1u },
	{ .bytes = "Wells",     .width = sizeof("Wells")		- 1u },
	{ .bytes = "West",      .width = sizeof("West")			- 1u },
	{ .bytes = "White",     .width = sizeof("White")		- 1u },
	{ .bytes = "Williams",  .width = sizeof("Williams")		- 1u },
	{ .bytes = "Willis",    .width = sizeof("Willis")		- 1u },
	{ .bytes = "Wilson",    .width = sizeof("Wilson")		- 1u },
	{ .bytes = "Wood",      .width = sizeof("Wood")			- 1u },
	{ .bytes = "Woods",     .width = sizeof("Woods")		- 1u },
	{ .bytes = "Wright",    .width = sizeof("Wright")		- 1u },
	{ .bytes = "Young",     .width = sizeof("Young")		- 1u }
};


const struct NameMap first_name_map = {
	.names  = &first_names[0],
	.i_last = FIRST_NAMES_COUNT - 1lu
};

const struct NameMap last_name_map = {
	.names  = &last_names[0],
	.i_last = LAST_NAMES_COUNT - 1lu
};

extern inline char *
put_random_initial(char *const restrict string);

extern inline const struct Stub *
name_map_sample(const struct NameMap *const restrict map);

extern inline char *
put_single_names(char *restrict ptr,
		 const struct NameMap *const restrict map,
		 size_t count);

extern inline char *
put_full_names(char *restrict ptr,
	       size_t count);


void
build_column_string_names_first(void *arg)
{
	struct Column *const restrict column
	= (struct Column *const restrict) arg;

	struct Table *const restrict table
	= column->parent;

	const struct Rowspan *const restrict until = table->rowspans_until;

	const unsigned int col_count = table->col_count;

	const size_t row_count = table->spec->row_count;

	if (row_count > FIRST_NAMES_COUNT_MAX) {
		handler_closure_call(&column->fail_cl,
				     BCSN_FIRST_MAX_EXCEEDED);
		__builtin_unreachable();
	}

	const size_t size_est = sizeof(char)
			      * (FIRST_NAME_SIZE_MAX * row_count);

	thread_try_catch_open(free,
			      column->contents);

	column->contents = malloc(size_est);

	if (column->contents == NULL) {
		handler_closure_call(&column->fail_cl,
				     BCSN_FIRST_MALLOC_FAILURE);
		__builtin_unreachable();
	}

	struct Rowspan *restrict from		   = column->rowspans_from;

	char *restrict ptr = column->contents;

	do {
		from->cell = ptr;

		ptr = put_single_names(ptr,
				       &first_name_map,
				       from->parent->row_count);

		/* add length of rowspan to row_block total */
		length_lock_increment(&from->parent->total,
				      ptr - from->cell,
				      &column->fail_cl);

		/* skip to rowspan in next row */
		from += col_count;
	} while (from < until);


	/* add length of column to table total */
	length_lock_increment(&table->total,
			      ptr - column->rowspans_from->cell,
			      &column->fail_cl);

	thread_try_catch_close();
}


void
build_column_string_names_last(void *arg)
{
	struct Column *const restrict column
	= (struct Column *const restrict) arg;

	struct Table *const restrict table
	= column->parent;

	const struct Rowspan *const restrict until = table->rowspans_until;

	const unsigned int col_count = table->col_count;

	const size_t row_count = table->spec->row_count;

	if (row_count > LAST_NAMES_COUNT_MAX) {
		handler_closure_call(&column->fail_cl,
				     BCSN_LAST_MAX_EXCEEDED);
		__builtin_unreachable();
	}

	const size_t size_est = sizeof(char) * (LAST_NAME_SIZE_MAX * row_count);

	thread_try_catch_open(free,
			      column->contents);

	column->contents = malloc(size_est);

	if (column->contents == NULL) {
		handler_closure_call(&column->fail_cl,
				     BCSN_LAST_MALLOC_FAILURE);
		__builtin_unreachable();
	}

	struct Rowspan *restrict from		   = column->rowspans_from;

	char *restrict ptr = column->contents;

	do {
		from->cell = ptr;

		ptr = put_single_names(ptr,
				       &last_name_map,
				       from->parent->row_count);

		/* add length of rowspan to row_block total */
		length_lock_increment(&from->parent->total,
				      ptr - from->cell,
				      &column->fail_cl);

		/* skip to rowspan in next row */
		from += col_count;
	} while (from < until);


	/* add length of column to table total */
	length_lock_increment(&table->total,
			      ptr - column->rowspans_from->cell,
			      &column->fail_cl);

	thread_try_catch_close();
}


void
build_column_string_names_full(void *arg)
{
	struct Column *const restrict column
	= (struct Column *const restrict) arg;

	struct Table *const restrict table
	= column->parent;

	const struct Rowspan *const restrict until = table->rowspans_until;

	const unsigned int col_count = table->col_count;

	const size_t row_count = table->spec->row_count;

	if (row_count > FULL_NAMES_COUNT_MAX) {
		handler_closure_call(&column->fail_cl,
				     BCSN_FULL_MAX_EXCEEDED);
		__builtin_unreachable();
	}

	const size_t size_est = sizeof(char) * (FULL_NAME_SIZE_MAX * row_count);


	thread_try_catch_open(free,
			      column->contents);

	column->contents = malloc(size_est);

	if (column->contents == NULL) {
		handler_closure_call(&column->fail_cl,
				     BCSN_FULL_MALLOC_FAILURE);
		__builtin_unreachable();
	}


	struct Rowspan *restrict from		   = column->rowspans_from;

	char *restrict ptr = column->contents;

	do {
		from->cell = ptr;

		ptr = put_full_names(ptr,
				     from->parent->row_count);

		/* add length of rowspan to row_block total */
		length_lock_increment(&from->parent->total,
				      ptr - from->cell,
				      &column->fail_cl);

		/* skip to rowspan in next row */
		from += col_count;
	} while (from < until);


	/* add length of column to table total */
	length_lock_increment(&table->total,
			      ptr - column->rowspans_from->cell,
			      &column->fail_cl);

	thread_try_catch_close();
}
