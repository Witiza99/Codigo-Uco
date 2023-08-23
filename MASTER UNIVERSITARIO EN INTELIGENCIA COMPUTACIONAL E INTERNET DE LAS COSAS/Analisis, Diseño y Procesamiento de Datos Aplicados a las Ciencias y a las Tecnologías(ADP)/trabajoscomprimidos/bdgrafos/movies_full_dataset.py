# Ejercicio 2
# Grafo completo 'Movie Graph'
# Supone la contraseña de la BDD es 'neo4j-ADP1'

from py2neo import Graph, Node, Relationship

AFewGoodMen = Node("Movie", title="A Few Good Men", released=1992,
                   tagline="In the heart of the nation's capital, in a courthouse of the U.S. government, one man will stop at nothing to keep his honor, and one will stop at nothing to find the truth.")
ALeagueofTheirOwn = Node("Movie", title='A League of Their Own', released=1992,
                         tagline='Once in a lifetime you get a chance to do something different.')
AaronS = Node("Person", name='Aaron Sorkin', born=1961)
Al = Node("Person", name='Al Pacino', born=1940)
AnnabellaS = Node("Person", name='Annabella Sciorra', born=1960)
AnthonyE = Node("Person", name='Anthony Edwards', born=1962)
Apollo13 = Node("Movie", title='Apollo 13', released=1995,
                tagline='Houston, we have a problem.')
AsGoodAsItGets = Node("Movie", title='As Good as It Gets', released=1997,
                      tagline='A comedy from the heart that goes for the throat.')
AudreyT = Node("Person", name='Audrey Tautou', born=1976)
BenM = Node("Person", name='Ben Miles', born=1967)
BicentennialMan = Node("Movie", title='Bicentennial Man', released=1999,
                       tagline="One robot's 200 year journey to become an ordinary man.")
BillPax = Node("Person", name='Bill Paxton', born=1955)
BillPull = Node("Person", name='Bill Pullman', born=1953)
BillyC = Node("Person", name='Billy Crystal', born=1948)
BonnieH = Node("Person", name='Bonnie Hunt', born=1961)
Brooke = Node("Person", name='Brooke Langton', born=1970)
BrunoK = Node("Person", name='Bruno Kirby', born=1949)
CameronC = Node("Person", name='Cameron Crowe', born=1957)
Carrie = Node("Person", name='Carrie-Anne Moss', born=1967)
CarrieF = Node("Person", name='Carrie Fisher', born=1956)
CastAway = Node("Movie", title='Cast Away', released=2000,
                tagline='At the edge of the world, his journey begins.')
CharlieWilsonsWar = Node("Movie", title="Charlie Wilson's War", released=2007,
                         tagline="A stiff drink. A little mascara. A lot of nerve. Who said they couldn't bring down the Soviet empire.")
Charlize = Node("Person", name='Charlize Theron', born=1975)
ChrisC = Node("Person", name='Chris Columbus', born=1958)
ChristianB = Node("Person", name='Christian Bale', born=1974)
ChristinaR = Node("Person", name='Christina Ricci', born=1980)
ChristopherG = Node("Person", name='Christopher Guest', born=1948)
ClintE = Node("Person", name='Clint Eastwood', born=1930)
CloudAtlas = Node("Movie", title='Cloud Atlas', released=2012,
                  tagline='Everything is connected')
CoreyF = Node("Person", name='Corey Feldman', born=1971)
CubaG = Node("Person", name='Cuba Gooding Jr.', born=1968)
DannyD = Node("Person", name='Danny DeVito', born=1944)
DaveC = Node("Person", name='Dave Chappelle', born=1973)
DavidM = Node("Person", name='David Morse', born=1953)
DavidMitchell = Node("Person", name='David Mitchell', born=1969)
DemiM = Node("Person", name='Demi Moore', born=1962)
DianeK = Node("Person", name='Diane Keaton', born=1946)
Dina = Node("Person", name='Dina Meyer', born=1968)
EdH = Node("Person", name='Ed Harris', born=1950)
Emil = Node("Person", name="Emil Eifrem", born=1978)
EmileH = Node("Person", name='Emile Hirsch', born=1985)
EthanH = Node("Person", name='Ethan Hawke', born=1970)
FrankD = Node("Person", name='Frank Darabont', born=1959)
FrankL = Node("Person", name='Frank Langella', born=1938)
FrostNixon = Node("Movie", title='Frost/Nixon', released=2008,
                  tagline='400 million people were waiting for the truth.')
GaryS = Node("Person", name='Gary Sinise', born=1955)
GeenaD = Node("Person", name='Geena Davis', born=1956)
Gene = Node("Person", name='Gene Hackman', born=1930)
GregK = Node("Person", name='Greg Kinnear', born=1963)
HalleB = Node("Person", name='Halle Berry', born=1966)
HelenH = Node("Person", name='Helen Hunt', born=1963)
Hoffa = Node("Movie", title='Hoffa', released=1992,
             tagline="He didn't want law. He wanted justice.")
Howard = Node("Person", name='Howard Deutch', born=1950)
Hugo = Node("Person", name='Hugo Weaving', born=1960)
IanM = Node("Person", name='Ian McKellen', born=1939)
IceT = Node("Person", name='Ice-T', born=1958)
JTW = Node("Person", name='J.T. Walsh', born=1943)
JackN = Node("Person", name='Jack Nicholson', born=1937)
JamesB = Node("Person", name='James L. Brooks', born=1940)
JamesC = Node("Person", name='James Cromwell', born=1940)
JamesM = Node("Person", name='James Marshall', born=1967)
JanB = Node("Person", name='Jan de Bont', born=1943)
JayM = Node("Person", name='Jay Mohr', born=1970)
JerryMaguire = Node("Movie", title='Jerry Maguire',
                    released=2000, tagline='The rest of his life begins now.')
JerryO = Node("Person", name="Jerry O'Connell", born=1974)
JimB = Node("Person", name='Jim Broadbent', born=1949)
JimC = Node("Person", name='Jim Cash', born=1941)
JoeVersustheVolcano = Node("Movie", title='Joe Versus the Volcano',
                           released=1990, tagline='A story of love, lava and burning desire.')
JoelS = Node("Person", name='Joel Silver', born=1952)
JohnC = Node("Person", name='John Cusack', born=1966)
JohnG = Node("Person", name='John Goodman', born=1960)
JohnH = Node("Person", name='John Hurt', born=1940)
JohnR = Node("Person", name='John C. Reilly', born=1965)
JohnS = Node("Person", name='John Patrick Stanley', born=1950)
JohnnyMnemonic = Node("Movie", title='Johnny Mnemonic', released=1995,
                      tagline='The hottest data on earth. In the coolest head in town')
JonathanL = Node("Person", name='Jonathan Lipnicki', born=1996)
JuliaR = Node("Person", name='Julia Roberts', born=1967)
Keanu = Node("Person", name='Keanu Reeves', born=1964)
KellyM = Node("Person", name='Kelly McGillis', born=1957)
KellyP = Node("Person", name='Kelly Preston', born=1962)
KevinB = Node("Person", name='Kevin Bacon', born=1958)
KevinP = Node("Person", name='Kevin Pollak', born=1957)
KieferS = Node("Person", name='Kiefer Sutherland', born=1966)
LanaW = Node("Person", name='Lana Wachowski', born=1965)
Laurence = Node("Person", name='Laurence Fishburne', born=1961)
LillyW = Node("Person", name='Lilly Wachowski', born=1967)
LivT = Node("Person", name='Liv Tyler', born=1977)
LoriP = Node("Person", name='Lori Petty', born=1963)
Madonna = Node("Person", name='Madonna', born=1954)
MarshallB = Node("Person", name='Marshall Bell', born=1942)
MatthewF = Node("Person", name='Matthew Fox', born=1966)
MaxS = Node("Person", name='Max von Sydow', born=1929)
MegR = Node("Person", name='Meg Ryan', born=1961)
MichaelD = Node("Person", name='Michael Clarke Duncan', born=1957)
MichaelS = Node("Person", name='Michael Sheen', born=1969)
MikeN = Node("Person", name='Mike Nichols', born=1931)
MilosF = Node("Person", name='Milos Forman', born=1932)
NancyM = Node("Person", name='Nancy Meyers', born=1949)
NaomieH = Node("Person", name='Naomie Harris')
NatalieP = Node("Person", name='Natalie Portman', born=1981)
Nathan = Node("Person", name='Nathan Lane', born=1956)
NinjaAssassin = Node("Movie", title='Ninja Assassin', released=2009,
                     tagline='Prepare to enter a secret world of assassins')
NoahW = Node("Person", name='Noah Wyle', born=1971)
NoraE = Node("Person", name='Nora Ephron', born=1941)
OliverP = Node("Person", name='Oliver Platt', born=1960)
OneFlewOvertheCuckoosNest = Node("Movie", title="One Flew Over the Cuckoo's Nest",
                                 released=1975, tagline="If he's crazy, what does that make you?")
Orlando = Node("Person", name='Orlando Jones', born=1968)
ParkerP = Node("Person", name='Parker Posey', born=1968)
PatriciaC = Node("Person", name='Patricia Clarkson', born=1959)
PaulB = Node("Person", name='Paul Bettany', born=1971)
PennyM = Node("Person", name='Penny Marshall', born=1943)
PhilipH = Node("Person", name='Philip Seymour Hoffman', born=1967)
Rain = Node("Person", name='Rain', born=1982)
ReginaK = Node("Person", name='Regina King', born=1971)
ReneeZ = Node("Person", name='Renee Zellweger', born=1969)
RescueDawn = Node("Movie", title='RescueDawn', released=2006,
                  tagline="Based on the extraordinary true story of one man's fight for freedom")
RichardH = Node("Person", name='Richard Harris', born=1930)
RickY = Node("Person", name='Rick Yune', born=1971)
RitaW = Node("Person", name='Rita Wilson', born=1956)
RiverP = Node("Person", name='River Phoenix', born=1970)
RobR = Node("Person", name='Rob Reiner', born=1947)
RobertL = Node("Person", name='Robert Longo', born=1953)
RobertZ = Node("Person", name='Robert Zemeckis', born=1951)
Robin = Node("Person", name='Robin Williams', born=1951)
RonH = Node("Person", name='Ron Howard', born=1954)
RosieO = Node("Person", name="Rosie O'Donnell", born=1962)
SamR = Node("Person", name='Sam Rockwell', born=1968)
ScottH = Node("Person", name='Scott Hicks', born=1953)
SleeplessInSeattle = Node("Movie", title='Sleepless in Seattle', released=1993,
                          tagline='What if someone you never met, someone you never saw, someone you never knew was the only someone for you?')
SnowFallingonCedars = Node("Movie", title='Snow Falling on Cedars',
                           released=1999, tagline='First loves last. Forever.')
SomethingsGottaGive = Node(
    "Movie", title="Something's Gotta Give", released=2003)
SpeedRacer = Node("Movie", title='Speed Racer',
                  released=2008, tagline='Speed has no limits')
StandByMe = Node("Movie", title="Stand By Me", released=1986,
                 tagline="For some, it's the last real taste of innocence, and the first real taste of life. But for everyone, it's the time that memories are made of.")
StefanArndt = Node("Person", name='Stefan Arndt', born=1961)
StephenR = Node("Person", name='Stephen Rea', born=1946)
SteveZ = Node("Person", name='Steve Zahn', born=1967)
SusanS = Node("Person", name='Susan Sarandon', born=1946)
Takeshi = Node("Person", name='Takeshi Kitano', born=1947)
Taylor = Node("Person", name='Taylor Hackford', born=1944)
ThatThingYouDo = Node("Movie", title='That Thing You Do', released=1996,
                      tagline='In every life there comes a time when that thing you dream becomes that thing you do')
TheBirdcage = Node("Movie", title='The Birdcage',
                   released=1996, tagline='Come as you are')
TheDaVinciCode = Node("Movie", title='The Da Vinci Code',
                      released=2006, tagline='Break The Codes')
TheDevilsAdvocate = Node("Movie", title="The Devil's Advocate",
                         released=1997, tagline='Evil has its winning ways')
TheGreenMile = Node("Movie", title='The Green Mile',
                    released=1999, tagline="Walk a mile you'll never forget.")
TheMatrix = Node("Movie", title='The Matrix', released=1999,
                 tagline='Welcome to the Real World')
TheMatrixReloaded = Node("Movie", title='The Matrix Reloaded',
                         released=2003, tagline='Free your mind')
TheMatrixRevolutions = Node("Movie", title='The Matrix Revolutions',
                            released=2003, tagline='Everything that has a beginning has an end')
ThePolarExpress = Node("Movie", title='The Polar Express',
                       released=2004, tagline='This Holiday Season… Believe')
TheReplacements = Node("Movie", title='The Replacements', released=2000,
                       tagline='Pain heals, Chicks dig scars... Glory lasts forever')
TomC = Node("Person", name='Tom Cruise', born=1962)
TomH = Node("Person", name='Tom Hanks', born=1956)
TomS = Node("Person", name='Tom Skerritt', born=1933)
TomT = Node("Person", name='Tom Tykwer', born=1965)
TonyS = Node("Person", name='Tony Scott', born=1944)
TopGun = Node("Movie", title="Top Gun", released=1986,
              tagline='I feel the need, the need for speed.')
Twister = Node("Movie", title='Twister', released=1996,
               tagline="Don't Breathe. Don't Look Back.")
Unforgiven = Node("Movie", title='Unforgiven', released=1992,
                  tagline="It's a hell of a thing, killing a man")
ValK = Node("Person", name='Val Kilmer', born=1959)
VforVendetta = Node("Movie", title='V for Vendetta',
                    released=2006, tagline='Freedom! Forever!')
VictorG = Node("Person", name='Victor Garber', born=1949)
VincentW = Node("Person", name='Vincent Ward', born=1956)
WernerH = Node("Person", name='Werner Herzog', born=1942)
WhatDreamsMayCome = Node("Movie", title='What Dreams May Come', released=1998,
                         tagline='After life there is more. The end is just the beginning.')
WhenHarryMetSally = Node("Movie", title='When Harry Met Sally',
                         released=1998, tagline='At odds in life... in love on-line.')
WilW = Node("Person", name='Wil Wheaton', born=1972)
YouveGotMail = Node("Movie", title="You've Got Mail",
                    released=1998, tagline='At odds in life... in love on-line.')
ZachG = Node("Person", name='Zach Grenier', born=1954)
AaronSAFewGoodMen = Relationship(AaronS, "WROTE", AFewGoodMen)
CameronCJerryMaguire = Relationship(CameronC, "WROTE", JerryMaguire)
ChrisCBicentennialMan = Relationship(ChrisC, "DIRECTED", BicentennialMan)
ClintEUnforgiven = Relationship(ClintE, "DIRECTED", Unforgiven)
DannyDHoffa = Relationship(DannyD, "DIRECTED", Hoffa)
FrankDTheGreenMile = Relationship(FrankD, "DIRECTED", TheGreenMile)
HowardTheReplacements = Relationship(Howard, "DIRECTED", TheReplacements)
JamesBAsGoodAsItGets = Relationship(JamesB, "DIRECTED", AsGoodAsItGets)
JanBTwister = Relationship(JanB, "DIRECTED", Twister)
JimCTopGun = Relationship(JimC, "WROTE", TopGun)
JoelSNinjaAssassin = Relationship(JoelS, "PRODUCED", NinjaAssassin)
JoelSSpeedRacer = Relationship(JoelS, "PRODUCED", SpeedRacer)
JoelSTheMatrix = Relationship(JoelS, "PRODUCED", TheMatrix)
JoelSTheMatrixReloaded = Relationship(JoelS, "PRODUCED", TheMatrixReloaded)
JoelSTheMatrixRevolutions = Relationship(
    JoelS, "PRODUCED", TheMatrixRevolutions)
JohnSJoeVersustheVolcano = Relationship(JohnS, "DIRECTED", JoeVersustheVolcano)
LanaWVforVendetta = Relationship(LanaW, "WROTE", VforVendetta)
MikeNCharlieWilsonsWar = Relationship(MikeN, "DIRECTED", CharlieWilsonsWar)
MikeNTheBirdcage = Relationship(MikeN, "DIRECTED", TheBirdcage)
MilosFOneFlewOvertheCuckoosNest = Relationship(
    MilosF, "DIRECTED", OneFlewOvertheCuckoosNest)
NancyMSomethingsGottaGive = Relationship(NancyM, "WROTE", SomethingsGottaGive)
NoraESleeplessInSeattle = Relationship(NoraE, "DIRECTED", SleeplessInSeattle)
NoraEYouveGotMail = Relationship(NoraE, "DIRECTED", YouveGotMail)
NoraEWhenHarryMetSally = Relationship(NoraE, "WROTE", WhenHarryMetSally)
PennyMALeagueofTheirOwn = Relationship(PennyM, "DIRECTED", ALeagueofTheirOwn)
RobRStandByMe = Relationship(RobR, "DIRECTED", StandByMe)
RobertLJohnnyMnemonic = Relationship(RobertL, "DIRECTED", JohnnyMnemonic)
RobertZCastAway = Relationship(RobertZ, "DIRECTED", CastAway)
RobertZThePolarExpress = Relationship(RobertZ, "DIRECTED", ThePolarExpress)
RonHApollo13 = Relationship(RonH, "DIRECTED", Apollo13)
RonHFrostNixon = Relationship(RonH, "DIRECTED", FrostNixon)
RonHTheDaVinciCode = Relationship(RonH, "DIRECTED", TheDaVinciCode)
ScottHSnowFallingonCedars = Relationship(
    ScottH, "DIRECTED", SnowFallingonCedars)
StefanArndtCloudAtlas = Relationship(StefanArndt, "PRODUCED", CloudAtlas)
TaylorTheDevilsAdvocate = Relationship(Taylor, "DIRECTED", TheDevilsAdvocate)
TomHThatThingYouDo = Relationship(TomH, "DIRECTED", ThatThingYouDo)
VincentWWhatDreamsMayCome = Relationship(
    VincentW, "DIRECTED", WhatDreamsMayCome)
WernerHRescueDawn = Relationship(WernerH, "DIRECTED", RescueDawn)
CameronCJerryMaguire = Relationship(CameronC, "DIRECTED", JerryMaguire)
CameronCJerryMaguire = Relationship(CameronC, "PRODUCED", JerryMaguire)
DavidMitchellCloudAtlas = Relationship(DavidMitchell, "WROTE", CloudAtlas)
JamesCSnowFallingonCedars = Relationship(
    JamesC, "ACTED_IN", SnowFallingonCedars)
JamesMNinjaAssassin = Relationship(JamesM, "DIRECTED", NinjaAssassin)
JamesMVforVendetta = Relationship(JamesM, "DIRECTED", VforVendetta)
JoelSVforVendetta = Relationship(JoelS, "PRODUCED", VforVendetta)
LanaWCloudAtlas = Relationship(LanaW, "DIRECTED", CloudAtlas)
LanaWSpeedRacer = Relationship(LanaW, "DIRECTED", SpeedRacer)
LanaWTheMatrix = Relationship(LanaW, "DIRECTED", TheMatrix)
LanaWTheMatrixReloaded = Relationship(LanaW, "DIRECTED", TheMatrixReloaded)
LanaWTheMatrixRevolutions = Relationship(
    LanaW, "DIRECTED", TheMatrixRevolutions)
LanaWNinjaAssassin = Relationship(LanaW, "PRODUCED", NinjaAssassin)
LanaWVforVendetta = Relationship(LanaW, "PRODUCED", VforVendetta)
LanaWSpeedRacer = Relationship(LanaW, "WROTE", SpeedRacer)
LillyWCloudAtlas = Relationship(LillyW, "DIRECTED", CloudAtlas)
LillyWSpeedRacer = Relationship(LillyW, "DIRECTED", SpeedRacer)
LillyWTheMatrix = Relationship(LillyW, "DIRECTED", TheMatrix)
LillyWTheMatrixReloaded = Relationship(LillyW, "DIRECTED", TheMatrixReloaded)
LillyWTheMatrixRevolutions = Relationship(
    LillyW, "DIRECTED", TheMatrixRevolutions)
LillyWNinjaAssassin = Relationship(LillyW, "PRODUCED", NinjaAssassin)
LillyWVforVendetta = Relationship(LillyW, "PRODUCED", VforVendetta)
LillyWSpeedRacer = Relationship(LillyW, "WROTE", SpeedRacer)
LillyWVforVendetta = Relationship(LillyW, "WROTE", VforVendetta)
NancyMSomethingsGottaGive = Relationship(
    NancyM, "DIRECTED", SomethingsGottaGive)
NancyMSomethingsGottaGive = Relationship(
    NancyM, "PRODUCED", SomethingsGottaGive)
NoraEWhenHarryMetSally = Relationship(NoraE, "PRODUCED", WhenHarryMetSally)
RobRAFewGoodMen = Relationship(RobR, "DIRECTED", AFewGoodMen)
RobRWhenHarryMetSally = Relationship(RobR, "DIRECTED", WhenHarryMetSally)
RobRWhenHarryMetSally = Relationship(RobR, "PRODUCED", WhenHarryMetSally)
TomTCloudAtlas = Relationship(TomT, "DIRECTED", CloudAtlas)
TonySTopGun = Relationship(TonyS, "DIRECTED", TopGun)
EmilTheMatrix = Relationship(Emil, "ACTED_IN", TheMatrix)
EmilTheMatrix['roles'] = ["Emil"]
MadonnaALeagueofTheirOwn = Relationship(Madonna, "ACTED_IN", ALeagueofTheirOwn)
MadonnaALeagueofTheirOwn['roles'] = ['"All the Way" Mae Mordabito']
SamRTheGreenMile = Relationship(SamR, "ACTED_IN", TheGreenMile)
SamRTheGreenMile['roles'] = ['"Wild Bill" Wharton']
KieferSStandByMe = Relationship(KieferS, "ACTED_IN", StandByMe)
KieferSStandByMe['roles'] = ['Ace Merrill']
MarshallBRescueDawn = Relationship(MarshallB, "ACTED_IN", RescueDawn)
MarshallBRescueDawn['roles'] = ['Admiral']
HugoTheMatrix = Relationship(Hugo, "ACTED_IN", TheMatrix)
HugoTheMatrix['roles'] = ['Agent Smith']
HugoTheMatrixReloaded = Relationship(Hugo, "ACTED_IN", TheMatrixReloaded)
HugoTheMatrixReloaded['roles'] = ['Agent Smith']
HugoTheMatrixRevolutions = Relationship(Hugo, "ACTED_IN", TheMatrixRevolutions)
HugoTheMatrixRevolutions['roles'] = ['Agent Smith']
NathanTheBirdcage = Relationship(Nathan, "ACTED_IN", TheBirdcage)
NathanTheBirdcage['roles'] = ['Albert Goldman']
CubaGWhatDreamsMayCome = Relationship(CubaG, "ACTED_IN", WhatDreamsMayCome)
CubaGWhatDreamsMayCome['roles'] = ['Albert Lewis']
RobinBicentennialMan = Relationship(Robin, "ACTED_IN", BicentennialMan)
RobinBicentennialMan['roles'] = ['Andrew Marin']
BrookeTheReplacements = Relationship(Brooke, "ACTED_IN", TheReplacements)
BrookeTheReplacements['roles'] = ['Annabelle Farrell']
AnnabellaSWhatDreamsMayCome = Relationship(
    AnnabellaS, "ACTED_IN", WhatDreamsMayCome)
AnnabellaSWhatDreamsMayCome['roles'] = ['Annie Collins-Nielsen']
MegRSleeplessInSeattle = Relationship(MegR, "ACTED_IN", SleeplessInSeattle)
MegRSleeplessInSeattle['roles'] = ['Annie Reed']
RobinTheBirdcage = Relationship(Robin, "ACTED_IN", TheBirdcage)
RobinTheBirdcage['roles'] = ['Armand Goldman']
KellyPJerryMaguire = Relationship(KellyP, "ACTED_IN", JerryMaguire)
KellyPJerryMaguire['roles'] = ['Avery Bishop']
NathanJoeVersustheVolcano = Relationship(
    Nathan, "ACTED_IN", JoeVersustheVolcano)
NathanJoeVersustheVolcano['roles'] = ['Baw']
RosieOSleeplessInSeattle = Relationship(RosieO, "ACTED_IN", SleeplessInSeattle)
RosieOSleeplessInSeattle['roles'] = ['Becky']
BillPaxTwister = Relationship(BillPax, "ACTED_IN", Twister)
BillPaxTwister['roles'] = ['Bill Harding']
ClintEUnforgiven = Relationship(ClintE, "ACTED_IN", Unforgiven)
ClintEUnforgiven['roles'] = ['Bill Munny']
HugoCloudAtlas = Relationship(Hugo, "ACTED_IN", CloudAtlas)
HugoCloudAtlas['roles'] = ['Bill Smoke', 'Haskell Moore',
                           'Tadeusz Kesselring', 'Nurse Noakes', 'Boardman Mephi', 'Old Georgie']
BillPaxALeagueofTheirOwn = Relationship(BillPax, "ACTED_IN", ALeagueofTheirOwn)
BillPaxALeagueofTheirOwn['roles'] = ['Bob Hinson']
JayMJerryMaguire = Relationship(JayM, "ACTED_IN", JerryMaguire)
JayMJerryMaguire['roles'] = ['Bob Sugar']
OliverPFrostNixon = Relationship(OliverP, "ACTED_IN", FrostNixon)
OliverPFrostNixon['roles'] = ['Bob Zelnick']
DavidMTheGreenMile = Relationship(DavidM, "ACTED_IN", TheGreenMile)
DavidMTheGreenMile['roles'] = ['Brutus "Brutal" Howell']
GarySTheGreenMile = Relationship(GaryS, "ACTED_IN", TheGreenMile)
GarySTheGreenMile['roles'] = ['Burt Hammersmith']
KevinBAFewGoodMen = Relationship(KevinB, "ACTED_IN", AFewGoodMen)
KevinBAFewGoodMen['roles'] = ['Capt. Jack Ross']
HelenHAsGoodAsItGets = Relationship(HelenH, "ACTED_IN", AsGoodAsItGets)
HelenHAsGoodAsItGets['roles'] = ['Carol Connelly']
MegRTopGun = Relationship(MegR, "ACTED_IN", TopGun)
MegRTopGun['roles'] = ['Carole']
BenMSpeedRacer = Relationship(BenM, "ACTED_IN", SpeedRacer)
BenMSpeedRacer['roles'] = ['Cass Jones']
KellyMTopGun = Relationship(KellyM, "ACTED_IN", TopGun)
KellyMTopGun['roles'] = ['Charlie']
RiverPStandByMe = Relationship(RiverP, "ACTED_IN", StandByMe)
RiverPStandByMe['roles'] = ['Chris Chambers']
RobinWhatDreamsMayCome = Relationship(Robin, "ACTED_IN", WhatDreamsMayCome)
RobinWhatDreamsMayCome['roles'] = ['Chris Nielsen']
TomHCastAway = Relationship(TomH, "ACTED_IN", CastAway)
TomHCastAway['roles'] = ['Chuck Noland']
OrlandoTheReplacements = Relationship(Orlando, "ACTED_IN", TheReplacements)
OrlandoTheReplacements['roles'] = ['Clifford Franklin']
JackNAFewGoodMen = Relationship(JackN, "ACTED_IN", AFewGoodMen)
JackNAFewGoodMen['roles'] = ['Col. Nathan R. Jessup']
CubaGAFewGoodMen = Relationship(CubaG, "ACTED_IN", AFewGoodMen)
CubaGAFewGoodMen['roles'] = ['Cpl. Carl Hammaker']
NoahWAFewGoodMen = Relationship(NoahW, "ACTED_IN", AFewGoodMen)
NoahWAFewGoodMen['roles'] = ['Cpl. Jeffrey Barnes']
BenMVforVendetta = Relationship(BenM, "ACTED_IN", VforVendetta)
BenMVforVendetta['roles'] = ['Dascomb']
MichaelSFrostNixon = Relationship(MichaelS, "ACTED_IN", FrostNixon)
MichaelSFrostNixon['roles'] = ['David Frost']
MegRJoeVersustheVolcano = Relationship(MegR, "ACTED_IN", JoeVersustheVolcano)
MegRJoeVersustheVolcano['roles'] = [
    'DeDe', 'Angelica Graynamore', 'Patricia Graynamore']
JohnCStandByMe = Relationship(JohnC, "ACTED_IN", StandByMe)
JohnCStandByMe['roles'] = ['Denny Lachance']
ChristianBRescueDawn = Relationship(ChristianB, "ACTED_IN", RescueDawn)
ChristianBRescueDawn['roles'] = ['Dieter Dengler']
RosieOALeagueofTheirOwn = Relationship(RosieO, "ACTED_IN", ALeagueofTheirOwn)
RosieOALeagueofTheirOwn['roles'] = ['Doris Murphy']
ReneeZJerryMaguire = Relationship(ReneeZ, "ACTED_IN", JerryMaguire)
ReneeZJerryMaguire['roles'] = ['Dorothy Boyd']
GeenaDALeagueofTheirOwn = Relationship(GeenaD, "ACTED_IN", ALeagueofTheirOwn)
GeenaDALeagueofTheirOwn['roles'] = ['Dottie Hinson']
HelenHTwister = Relationship(HelenH, "ACTED_IN", Twister)
HelenHTwister['roles'] = ['Dr. Jo Harding']
TomHTheDaVinciCode = Relationship(TomH, "ACTED_IN", TheDaVinciCode)
TomHTheDaVinciCode['roles'] = ['Dr. Robert Langdon']
ChristopherGAFewGoodMen = Relationship(ChristopherG, "ACTED_IN", AFewGoodMen)
ChristopherGAFewGoodMen['roles'] = ['Dr. Stone']
SteveZRescueDawn = Relationship(SteveZ, "ACTED_IN", RescueDawn)
SteveZRescueDawn['roles'] = ['Duane']
PhilipHTwister = Relationship(PhilipH, "ACTED_IN", Twister)
PhilipHTwister['roles'] = ['Dustin "Dusty" Davis']
ZachGTwister = Relationship(ZachG, "ACTED_IN", Twister)
ZachGTwister['roles'] = ['Eddie']
RichardHUnforgiven = Relationship(RichardH, "ACTED_IN", Unforgiven)
RichardHUnforgiven['roles'] = ['English Bob']
StephenRVforVendetta = Relationship(StephenR, "ACTED_IN", VforVendetta)
VforVendetta['roles'] = ['Eric Finch']
DianeKSomethingsGottaGive = Relationship(
    DianeK, "ACTED_IN", SomethingsGottaGive)
DianeKSomethingsGottaGive['roles'] = ['Erica Barry']
NataliePVforVendetta = Relationship(NatalieP, "ACTED_IN", VforVendetta)
NataliePVforVendetta['roles'] = ['Evey Hammond']
LivTThatThingYouDo = Relationship(LivT, "ACTED_IN", ThatThingYouDo)
LivTThatThingYouDo['roles'] = ['Faye Dolan']
JerryOJerryMaguire = Relationship(JerryO, "ACTED_IN", JerryMaguire)
JerryOJerryMaguire['roles'] = ['Frank Cushman']
JTWHoffa = Relationship(JTW, "ACTED_IN", Hoffa)
JTWHoffa['roles'] = ['Frank Fitzsimmons']
GregKYouveGotMail = Relationship(GregK, "ACTED_IN", YouveGotMail)
GregKYouveGotMail['roles'] = ['Frank Navasky']
CubaGAsGoodAsItGets = Relationship(CubaG, "ACTED_IN", AsGoodAsItGets)
CubaGAsGoodAsItGets['roles'] = ['Frank Sachs']
BillPaxApollo13 = Relationship(BillPax, "ACTED_IN", Apollo13)
BillPaxApollo13['roles'] = ['Fred Haise']
EdHApollo13 = Relationship(EdH, "ACTED_IN", Apollo13)
EdHApollo13['roles'] = ['Gene Kranz']
SteveZYouveGotMail = Relationship(SteveZ, "ACTED_IN", YouveGotMail)
SteveZYouveGotMail['roles'] = ['George Pappas']
AnthonyETopGun = Relationship(AnthonyE, "ACTED_IN", TopGun)
AnthonyETopGun['roles'] = ['Goose']
WilWStandByMe = Relationship(WilW, "ACTED_IN", StandByMe)
WilWStandByMe['roles'] = ['Gordie Lachance']
VictorGSleeplessInSeattle = Relationship(
    VictorG, "ACTED_IN", SleeplessInSeattle)
VictorGSleeplessInSeattle['roles'] = ['Greg']
PhilipHCharlieWilsonsWar = Relationship(PhilipH, "ACTED_IN", CharlieWilsonsWar)
PhilipHCharlieWilsonsWar['roles'] = ['Gust Avrakotos']
BillyCWhenHarryMetSally = Relationship(BillyC, "ACTED_IN", WhenHarryMetSally)
BillyCWhenHarryMetSally['roles'] = ['Harry Burns']
JackNSomethingsGottaGive = Relationship(JackN, "ACTED_IN", SomethingsGottaGive)
JackNSomethingsGottaGive['roles'] = ['Harry Sanborn']
TomHThePolarExpress = Relationship(TomH, "ACTED_IN", ThePolarExpress)
TomHThePolarExpress['roles'] = ['Hero Boy', 'Father',
                                'Conductor', 'Hobo', 'Scrooge', 'Santa Claus']
JohnHVforVendetta = Relationship(JohnH, "ACTED_IN", VforVendetta)
JohnHVforVendetta['roles'] = ['High Chancellor Adam Sutler']
JackNHoffa = Relationship(JackN, "ACTED_IN", Hoffa)
JackNHoffa['roles'] = ['Hoffa']
ValKTopGun = Relationship(ValK, "ACTED_IN", TopGun)
ValKTopGun['roles'] = ['Iceman']
EthanHSnowFallingonCedars = Relationship(
    EthanH, "ACTED_IN", SnowFallingonCedars)
EthanHSnowFallingonCedars['roles'] = ['Ishmael Chambers']
IceTJohnnyMnemonic = Relationship(IceT, "ACTED_IN", JohnnyMnemonic)
IceTJohnnyMnemonic['roles'] = ['J-Bone']
KevinBFrostNixon = Relationship(KevinB, "ACTED_IN", FrostNixon)
KevinBFrostNixon['roles'] = ['Jack Brennan']
KevinBApollo13 = Relationship(KevinB, "ACTED_IN", Apollo13)
KevinBApollo13['roles'] = ['Jack Swigert']
SamRFrostNixon = Relationship(SamR, "ACTED_IN", FrostNixon)
SamRFrostNixon['roles'] = ['James Reston, Jr.']
BonnieHTheGreenMile = Relationship(BonnieH, "ACTED_IN", TheGreenMile)
BonnieHTheGreenMile['roles'] = ['Jan Edgecomb']
DinaJohnnyMnemonic = Relationship(Dina, "ACTED_IN", JohnnyMnemonic)
DinaJohnnyMnemonic['roles'] = ['Jane']
TomCJerryMaguire = Relationship(TomC, "ACTED_IN", JerryMaguire)
TomCJerryMaguire['roles'] = ['Jerry Maguire']
BrunoKWhenHarryMetSally = Relationship(BrunoK, "ACTED_IN", WhenHarryMetSally)
BrunoKWhenHarryMetSally['roles'] = ['Jess']
TomHApollo13 = Relationship(TomH, "ACTED_IN", Apollo13)
TomHApollo13['roles'] = ['Jim Lovell']
TomHALeagueofTheirOwn = Relationship(TomH, "ACTED_IN", ALeagueofTheirOwn)
TomHALeagueofTheirOwn['roles'] = ['Jimmy Dugan']
GeneTheReplacements = Relationship(Gene, "ACTED_IN", TheReplacements)
GeneTheReplacements['roles'] = ['Jimmy McGinty']
JuliaRCharlieWilsonsWar = Relationship(JuliaR, "ACTED_IN", CharlieWilsonsWar)
JuliaRCharlieWilsonsWar['roles'] = ['Joanne Herring']
TomHJoeVersustheVolcano = Relationship(TomH, "ACTED_IN", JoeVersustheVolcano)
TomHJoeVersustheVolcano['roles'] = ['Joe Banks']
TomHYouveGotMail = Relationship(TomH, "ACTED_IN", YouveGotMail)
TomHYouveGotMail['roles'] = ['Joe Fox']
MichaelDTheGreenMile = Relationship(MichaelD, "ACTED_IN", TheGreenMile)
MichaelDTheGreenMile['roles'] = ['John Coffey']
AlTheDevilsAdvocate = Relationship(Al, "ACTED_IN", TheDevilsAdvocate)
AlTheDevilsAdvocate['roles'] = ['John Milton']
KeanuJohnnyMnemonic = Relationship(Keanu, "ACTED_IN", JohnnyMnemonic)
KeanuJohnnyMnemonic['roles'] = ['Johnny Mnemonic']
JamesCSnowFallingonCedars = Relationship(
    JamesC, "ACTED_IN", SnowFallingonCedars)
JamesCSnowFallingonCedars['roles'] = ['Judge Fielding']
KeanuSomethingsGottaGive = Relationship(Keanu, "ACTED_IN", SomethingsGottaGive)
KeanuSomethingsGottaGive['roles'] = ['Julian Mercer']
MegRYouveGotMail = Relationship(MegR, "ACTED_IN", YouveGotMail)
MegRYouveGotMail['roles'] = ['Kathleen Kelly']
RickYSnowFallingonCedars = Relationship(RickY, "ACTED_IN", SnowFallingonCedars)
RickYSnowFallingonCedars['roles'] = ['Kazuo Miyamoto']
HelenHCastAway = Relationship(HelenH, "ACTED_IN", CastAway)
HelenHCastAway['roles'] = ['Kelly Frears']
GarySApollo13 = Relationship(GaryS, "ACTED_IN", Apollo13)
GarySApollo13['roles'] = ['Ken Mattingly']
DaveCYouveGotMail = Relationship(DaveC, "ACTED_IN", YouveGotMail)
DaveCYouveGotMail['roles'] = ['Kevin Jackson']
KeanuTheDevilsAdvocate = Relationship(Keanu, "ACTED_IN", TheDevilsAdvocate)
KeanuTheDevilsAdvocate['roles'] = ['Kevin Lomax']
LoriPALeagueofTheirOwn = Relationship(LoriP, "ACTED_IN", ALeagueofTheirOwn)
LoriPALeagueofTheirOwn['roles'] = ['Kit Keller']
BonnieHJerryMaguire = Relationship(BonnieH, "ACTED_IN", JerryMaguire)
BonnieHJerryMaguire['roles'] = ['Laurel Boyd']
GeneUnforgiven = Relationship(Gene, "ACTED_IN", Unforgiven)
GeneUnforgiven['roles'] = ['Little Bill Daggett']
DemiMAFewGoodMen = Relationship(DemiM, "ACTED_IN", AFewGoodMen)
DemiMAFewGoodMen['roles'] = ['Lt. Cdr. JoAnne Galloway']
JTWAFewGoodMen = Relationship(JTW, "ACTED_IN", AFewGoodMen)
JTWAFewGoodMen['roles'] = ['Lt. Col. Matthew Andrew Markinson']
TomCAFewGoodMen = Relationship(TomC, "ACTED_IN", AFewGoodMen)
TomCAFewGoodMen['roles'] = ['Lt. Daniel Kaffee']
KieferSAFewGoodMen = Relationship(KieferS, "ACTED_IN", AFewGoodMen)
KieferSAFewGoodMen['roles'] = ['Lt. Jonathan Kendrick']
KevinPAFewGoodMen = Relationship(KevinP, "ACTED_IN", AFewGoodMen)
KevinPAFewGoodMen['roles'] = ['Lt. Sam Weinberg']
HalleBCloudAtlas = Relationship(HalleB, "ACTED_IN", CloudAtlas)
HalleBCloudAtlas['roles'] = ['Luisa Rey', 'Jocasta Ayrs', 'Ovid', 'Meronym']
AaronSAFewGoodMen = Relationship(AaronS, "ACTED_IN", AFewGoodMen)
AaronSAFewGoodMen['roles'] = ['Man in Bar']
ReginaKJerryMaguire = Relationship(ReginaK, "ACTED_IN", JerryMaguire)
ReginaKJerryMaguire['roles'] = ['Marcee Tidwell']
CarrieFWhenHarryMetSally = Relationship(CarrieF, "ACTED_IN", WhenHarryMetSally)
CarrieFWhenHarryMetSally['roles'] = ['Marie']
DannyDOneFlewOvertheCuckoosNest = Relationship(
    DannyD, "ACTED_IN", OneFlewOvertheCuckoosNest)
DannyDOneFlewOvertheCuckoosNest['roles'] = ['Martini']
CharlizeTheDevilsAdvocate = Relationship(
    Charlize, "ACTED_IN", TheDevilsAdvocate)
CharlizeTheDevilsAdvocate['roles'] = ['Mary Ann Lomax']
TomCTopGun = Relationship(TomC, "ACTED_IN", TopGun)
TomCTopGun['roles'] = ['Maverick']
PatriciaCTheGreenMile = Relationship(PatriciaC, "ACTED_IN", TheGreenMile)
PatriciaCTheGreenMile['roles'] = ['Melinda Moores']
JackNAsGoodAsItGets = Relationship(JackN, "ACTED_IN", AsGoodAsItGets)
JackNAsGoodAsItGets['roles'] = ['Melvin Udall']
NaomieHNinjaAssassin = Relationship(NaomieH, "ACTED_IN", NinjaAssassin)
NaomieHNinjaAssassin['roles'] = ['Mika Coretti']
SusanSSpeedRacer = Relationship(SusanS, "ACTED_IN", SpeedRacer)
SusanSSpeedRacer['roles'] = ['Mom']
LaurenceTheMatrix = Relationship(Laurence, "ACTED_IN", TheMatrix)
LaurenceTheMatrix['roles'] = ['Morpheus']
LaurenceTheMatrixReloaded = Relationship(
    Laurence, "ACTED_IN", TheMatrixReloaded)
LaurenceTheMatrixReloaded['roles'] = ['Morpheus']
LaurenceTheMatrixRevolutions = Relationship(
    Laurence, "ACTED_IN", TheMatrixRevolutions)
LaurenceTheMatrixRevolutions['roles'] = ['Morpheus']
MarshallBStandByMe = Relationship(MarshallB, "ACTED_IN", StandByMe)
MarshallBStandByMe['roles'] = ['Mr. Lachance']
TomHThatThingYouDo = Relationship(TomH, "ACTED_IN", ThatThingYouDo)
TomHThatThingYouDo['roles'] = ['Mr. White']
MaxSSnowFallingonCedars = Relationship(MaxS, "ACTED_IN", SnowFallingonCedars)
MaxSSnowFallingonCedars['roles'] = ['Nels Gudmundsson']
KeanuTheMatrix = Relationship(Keanu, "ACTED_IN", TheMatrix)
KeanuTheMatrix['roles'] = ['Neo']
KeanuTheMatrixReloaded = Relationship(Keanu, "ACTED_IN", TheMatrixReloaded)
KeanuTheMatrixReloaded['roles'] = ['Neo']
KeanuTheMatrixRevolutions = Relationship(
    Keanu, "ACTED_IN", TheMatrixRevolutions)
KeanuTheMatrixRevolutions['roles'] = ['Neo']
ParkerPYouveGotMail = Relationship(ParkerP, "ACTED_IN", YouveGotMail)
ParkerPYouveGotMail['roles'] = ['Patricia Eden']
TomHTheGreenMile = Relationship(TomH, "ACTED_IN", TheGreenMile)
TomHTheGreenMile['roles'] = ['Paul Edgecomb']
JohnRHoffa = Relationship(JohnR, "ACTED_IN", Hoffa)
JohnRHoffa['roles'] = ['Peter "Pete" Connelly']
JamesMAFewGoodMen = Relationship(JamesM, "ACTED_IN", AFewGoodMen)
JamesMAFewGoodMen['roles'] = ['Pfc. Louden Downey']
JohnGSpeedRacer = Relationship(JohnG, "ACTED_IN", SpeedRacer)
JohnGSpeedRacer['roles'] = ['Pops']
MatthewFSpeedRacer = Relationship(MatthewF, "ACTED_IN", SpeedRacer)
MatthewFSpeedRacer['roles'] = ['Racer X']
RainNinjaAssassin = Relationship(Rain, "ACTED_IN", NinjaAssassin)
RainNinjaAssassin['roles'] = ['Raizo']
JackNOneFlewOvertheCuckoosNest = Relationship(
    JackN, "ACTED_IN", OneFlewOvertheCuckoosNest)
JackNOneFlewOvertheCuckoosNest['roles'] = ['Randle McMurphy']
JonathanLJerryMaguire = Relationship(JonathanL, "ACTED_IN", JerryMaguire)
JonathanLJerryMaguire['roles'] = ['Ray Boyd']
TomHCharlieWilsonsWar = Relationship(TomH, "ACTED_IN", CharlieWilsonsWar)
TomHCharlieWilsonsWar['roles'] = ['Rep. Charlie Wilson']
FrankLFrostNixon = Relationship(FrankL, "ACTED_IN", FrostNixon)
FrankLFrostNixon['roles'] = ['Richard Nixon']
DannyDHoffa = Relationship(DannyD, "ACTED_IN", Hoffa)
DannyDHoffa['roles'] = ['Robert "Bobby" Ciaro']
CubaGJerryMaguire = Relationship(CubaG, "ACTED_IN", JerryMaguire)
CubaGJerryMaguire['roles'] = ['Rod Tidwell']
OliverPBicentennialMan = Relationship(OliverP, "ACTED_IN", BicentennialMan)
OliverPBicentennialMan['roles'] = ['Rupert Burns']
BenMNinjaAssassin = Relationship(BenM, "ACTED_IN", NinjaAssassin)
BenMNinjaAssassin['roles'] = ['Ryan Maslow']
MegRWhenHarryMetSally = Relationship(MegR, "ACTED_IN", WhenHarryMetSally)
MegRWhenHarryMetSally['roles'] = ['Sally Albright']
TomHSleeplessInSeattle = Relationship(TomH, "ACTED_IN", SleeplessInSeattle)
TomHSleeplessInSeattle['roles'] = ['Sam Baldwin']
GeneTheBirdcage = Relationship(Gene, "ACTED_IN", TheBirdcage)
GeneTheBirdcage['roles'] = ['Sen. Kevin Keeley']
KeanuTheReplacements = Relationship(Keanu, "ACTED_IN", TheReplacements)
KeanuTheReplacements['roles'] = ['Shane Falco']
PaulBTheDaVinciCode = Relationship(PaulB, "ACTED_IN", TheDaVinciCode)
PaulBTheDaVinciCode['roles'] = ['Silas']
GregKAsGoodAsItGets = Relationship(GregK, "ACTED_IN", AsGoodAsItGets)
GregKAsGoodAsItGets['roles'] = ['Simon Bishop']
IanMTheDaVinciCode = Relationship(IanM, "ACTED_IN", TheDaVinciCode)
IanMTheDaVinciCode['roles'] = ['Sir Leight Teabing']
AudreyTTheDaVinciCode = Relationship(AudreyT, "ACTED_IN", TheDaVinciCode)
AudreyTTheDaVinciCode['roles'] = ['Sophie Neveu']
EmileHSpeedRacer = Relationship(EmileH, "ACTED_IN", SpeedRacer)
EmileHSpeedRacer['roles'] = ['Speed Racer']
ZachGRescueDawn = Relationship(ZachG, "ACTED_IN", RescueDawn)
ZachGRescueDawn['roles'] = ['Squad Leader']
RitaWSleeplessInSeattle = Relationship(RitaW, "ACTED_IN", SleeplessInSeattle)
RitaWSleeplessInSeattle['roles'] = ['Suzy']
RainSpeedRacer = Relationship(Rain, "ACTED_IN", SpeedRacer)
RainSpeedRacer['roles'] = ['Taejo Togokahn']
TakeshiJohnnyMnemonic = Relationship(Takeshi, "ACTED_IN", JohnnyMnemonic)
TakeshiJohnnyMnemonic['roles'] = ['Takahashi']
RickYNinjaAssassin = Relationship(RickY, "ACTED_IN", NinjaAssassin)
RickYNinjaAssassin['roles'] = ['Takeshi']
CoreyFStandByMe = Relationship(CoreyF, "ACTED_IN", StandByMe)
CoreyFStandByMe['roles'] = ['Teddy Duchamp']
WernerHWhatDreamsMayCome = Relationship(WernerH, "ACTED_IN", WhatDreamsMayCome)
WernerHWhatDreamsMayCome['roles'] = ['The Face']
MaxSWhatDreamsMayCome = Relationship(MaxS, "ACTED_IN", WhatDreamsMayCome)
MaxSWhatDreamsMayCome['roles'] = ['The Tracker']
CharlizeThatThingYouDo = Relationship(Charlize, "ACTED_IN", ThatThingYouDo)
CharlizeThatThingYouDo['roles'] = ['Tina']
CarrieTheMatrix = Relationship(Carrie, "ACTED_IN", TheMatrix)
CarrieTheMatrix['roles'] = ['Trinity']
CarrieTheMatrixReloaded = Relationship(Carrie, "ACTED_IN", TheMatrixReloaded)
CarrieTheMatrixReloaded['roles'] = ['Trinity']
CarrieTheMatrixRevolutions = Relationship(
    Carrie, "ACTED_IN", TheMatrixRevolutions)
CarrieTheMatrixRevolutions['roles'] = ['Trinity']
ChristinaRSpeedRacer = Relationship(ChristinaR, "ACTED_IN", SpeedRacer)
ChristinaRSpeedRacer['roles'] = ['Trixie']
HugoVforVendetta = Relationship(Hugo, "ACTED_IN", VforVendetta)
HugoVforVendetta['roles'] = ['V']
JerryOStandByMe = Relationship(JerryO, "ACTED_IN", StandByMe)
JerryOStandByMe['roles'] = ['Vern Tessio']
TomSTopGun = Relationship(TomS, "ACTED_IN", TopGun)
TomSTopGun['roles'] = ['Viper']
JimBCloudAtlas = Relationship(JimB, "ACTED_IN", CloudAtlas)
JimBCloudAtlas['roles'] = ['Vyvyan Ayrs',
                           'Captain Molyneux', 'Timothy Cavendish']
BillPullSleeplessInSeattle = Relationship(
    BillPull, "ACTED_IN", SleeplessInSeattle)
BillPullSleeplessInSeattle['roles'] = ['Walter']
JamesCTheGreenMile = Relationship(JamesC, "ACTED_IN", TheGreenMile)
JamesCTheGreenMile['roles'] = ['Warden Hal Moores']
TomHCloudAtlas = Relationship(TomH, "ACTED_IN", CloudAtlas)
TomHCloudAtlas['roles'] = [
    'Zachry', 'Dr. Henry Goose', 'Isaac Sachs', 'Dermot Hoggins']


graph = Graph(password='neo4j-ADP1')
tx = graph.begin()
tx.create(AFewGoodMen)
tx.create(ALeagueofTheirOwn)
tx.create(AaronS)
tx.create(Al)
tx.create(AnnabellaS)
tx.create(AnthonyE)
tx.create(Apollo13)
tx.create(AsGoodAsItGets)
tx.create(AudreyT)
tx.create(BenM)
tx.create(BicentennialMan)
tx.create(BillPax)
tx.create(BillPull)
tx.create(BillyC)
tx.create(BonnieH)
tx.create(Brooke)
tx.create(BrunoK)
tx.create(CameronC)
tx.create(Carrie)
tx.create(CarrieF)
tx.create(CastAway)
tx.create(CharlieWilsonsWar)
tx.create(Charlize)
tx.create(ChrisC)
tx.create(ChristianB)
tx.create(ChristinaR)
tx.create(ChristopherG)
tx.create(ClintE)
tx.create(CloudAtlas)
tx.create(CoreyF)
tx.create(CubaG)
tx.create(DannyD)
tx.create(DaveC)
tx.create(DavidM)
tx.create(DavidMitchell)
tx.create(DemiM)
tx.create(DianeK)
tx.create(Dina)
tx.create(EdH)
tx.create(Emil)
tx.create(EmileH)
tx.create(EthanH)
tx.create(FrankD)
tx.create(FrankL)
tx.create(FrostNixon)
tx.create(GaryS)
tx.create(GeenaD)
tx.create(Gene)
tx.create(GregK)
tx.create(HalleB)
tx.create(HelenH)
tx.create(Hoffa)
tx.create(Howard)
tx.create(Hugo)
tx.create(IanM)
tx.create(IceT)
tx.create(JTW)
tx.create(JackN)
tx.create(JamesB)
tx.create(JamesC)
tx.create(JamesM)
tx.create(JanB)
tx.create(JayM)
tx.create(JerryMaguire)
tx.create(JerryO)
tx.create(JimB)
tx.create(JimC)
tx.create(JoeVersustheVolcano)
tx.create(JoelS)
tx.create(JohnC)
tx.create(JohnG)
tx.create(JohnH)
tx.create(JohnR)
tx.create(JohnS)
tx.create(JohnnyMnemonic)
tx.create(JonathanL)
tx.create(JuliaR)
tx.create(Keanu)
tx.create(KellyM)
tx.create(KellyP)
tx.create(KevinB)
tx.create(KevinP)
tx.create(KieferS)
tx.create(LanaW)
tx.create(Laurence)
tx.create(LillyW)
tx.create(LivT)
tx.create(LoriP)
tx.create(Madonna)
tx.create(MarshallB)
tx.create(MatthewF)
tx.create(MaxS)
tx.create(MegR)
tx.create(MichaelD)
tx.create(MichaelS)
tx.create(MikeN)
tx.create(MilosF)
tx.create(NancyM)
tx.create(NaomieH)
tx.create(NatalieP)
tx.create(Nathan)
tx.create(NinjaAssassin)
tx.create(NoahW)
tx.create(NoraE)
tx.create(OliverP)
tx.create(OneFlewOvertheCuckoosNest)
tx.create(Orlando)
tx.create(ParkerP)
tx.create(PatriciaC)
tx.create(PaulB)
tx.create(PennyM)
tx.create(PhilipH)
tx.create(Rain)
tx.create(ReginaK)
tx.create(ReneeZ)
tx.create(RescueDawn)
tx.create(RichardH)
tx.create(RickY)
tx.create(RitaW)
tx.create(RiverP)
tx.create(RobR)
tx.create(RobertL)
tx.create(RobertZ)
tx.create(Robin)
tx.create(RonH)
tx.create(RosieO)
tx.create(SamR)
tx.create(ScottH)
tx.create(SleeplessInSeattle)
tx.create(SnowFallingonCedars)
tx.create(SomethingsGottaGive)
tx.create(SpeedRacer)
tx.create(StandByMe)
tx.create(StefanArndt)
tx.create(StephenR)
tx.create(SteveZ)
tx.create(SusanS)
tx.create(Takeshi)
tx.create(Taylor)
tx.create(ThatThingYouDo)
tx.create(TheBirdcage)
tx.create(TheDaVinciCode)
tx.create(TheDevilsAdvocate)
tx.create(TheGreenMile)
tx.create(TheMatrix)
tx.create(TheMatrixReloaded)
tx.create(TheMatrixRevolutions)
tx.create(ThePolarExpress)
tx.create(TheReplacements)
tx.create(TomC)
tx.create(TomH)
tx.create(TomS)
tx.create(TomT)
tx.create(TonyS)
tx.create(TopGun)
tx.create(Twister)
tx.create(Unforgiven)
tx.create(ValK)
tx.create(VforVendetta)
tx.create(VictorG)
tx.create(VincentW)
tx.create(WernerH)
tx.create(WhatDreamsMayCome)
tx.create(WhenHarryMetSally)
tx.create(WilW)
tx.create(YouveGotMail)
tx.create(ZachG)
tx.create(AaronSAFewGoodMen)
tx.create(CameronCJerryMaguire)
tx.create(ChrisCBicentennialMan)
tx.create(ClintEUnforgiven)
tx.create(DannyDHoffa)
tx.create(FrankDTheGreenMile)
tx.create(HowardTheReplacements)
tx.create(JamesBAsGoodAsItGets)
tx.create(JanBTwister)
tx.create(JimCTopGun)
tx.create(JoelSNinjaAssassin)
tx.create(JoelSSpeedRacer)
tx.create(JoelSTheMatrix)
tx.create(JoelSTheMatrixReloaded)
tx.create(JoelSTheMatrixRevolutions)
tx.create(JohnSJoeVersustheVolcano)
tx.create(LanaWVforVendetta)
tx.create(MikeNCharlieWilsonsWar)
tx.create(MikeNTheBirdcage)
tx.create(MilosFOneFlewOvertheCuckoosNest)
tx.create(NancyMSomethingsGottaGive)
tx.create(NoraESleeplessInSeattle)
tx.create(NoraEYouveGotMail)
tx.create(NoraEWhenHarryMetSally)
tx.create(PennyMALeagueofTheirOwn)
tx.create(RobRStandByMe)
tx.create(RobertLJohnnyMnemonic)
tx.create(RobertZCastAway)
tx.create(RobertZThePolarExpress)
tx.create(RonHApollo13)
tx.create(RonHFrostNixon)
tx.create(RonHTheDaVinciCode)
tx.create(ScottHSnowFallingonCedars)
tx.create(StefanArndtCloudAtlas)
tx.create(TaylorTheDevilsAdvocate)
tx.create(TomHThatThingYouDo)
tx.create(VincentWWhatDreamsMayCome)
tx.create(WernerHRescueDawn)
tx.create(CameronCJerryMaguire)
tx.create(CameronCJerryMaguire)
tx.create(DavidMitchellCloudAtlas)
tx.create(JamesCSnowFallingonCedars)
tx.create(JamesMNinjaAssassin)
tx.create(JamesMVforVendetta)
tx.create(JoelSVforVendetta)
tx.create(LanaWCloudAtlas)
tx.create(LanaWSpeedRacer)
tx.create(LanaWTheMatrix)
tx.create(LanaWTheMatrixReloaded)
tx.create(LanaWTheMatrixRevolutions)
tx.create(LanaWNinjaAssassin)
tx.create(LanaWVforVendetta)
tx.create(LanaWSpeedRacer)
tx.create(LillyWCloudAtlas)
tx.create(LillyWSpeedRacer)
tx.create(LillyWTheMatrix)
tx.create(LillyWTheMatrixReloaded)
tx.create(LillyWTheMatrixRevolutions)
tx.create(LillyWNinjaAssassin)
tx.create(LillyWVforVendetta)
tx.create(LillyWSpeedRacer)
tx.create(LillyWVforVendetta)
tx.create(NancyMSomethingsGottaGive)
tx.create(NancyMSomethingsGottaGive)
tx.create(NoraEWhenHarryMetSally)
tx.create(RobRAFewGoodMen)
tx.create(RobRWhenHarryMetSally)
tx.create(RobRWhenHarryMetSally)
tx.create(TomTCloudAtlas)
tx.create(TonySTopGun)
tx.create(EmilTheMatrix)
tx.create(MadonnaALeagueofTheirOwn)
tx.create(SamRTheGreenMile)
tx.create(KieferSStandByMe)
tx.create(MarshallBRescueDawn)
tx.create(HugoTheMatrix)
tx.create(HugoTheMatrixReloaded)
tx.create(HugoTheMatrixRevolutions)
tx.create(NathanTheBirdcage)
tx.create(CubaGWhatDreamsMayCome)
tx.create(RobinBicentennialMan)
tx.create(BrookeTheReplacements)
tx.create(AnnabellaSWhatDreamsMayCome)
tx.create(MegRSleeplessInSeattle)
tx.create(RobinTheBirdcage)
tx.create(KellyPJerryMaguire)
tx.create(NathanJoeVersustheVolcano)
tx.create(RosieOSleeplessInSeattle)
tx.create(BillPaxTwister)
tx.create(ClintEUnforgiven)
tx.create(HugoCloudAtlas)
tx.create(BillPaxALeagueofTheirOwn)
tx.create(JayMJerryMaguire)
tx.create(OliverPFrostNixon)
tx.create(DavidMTheGreenMile)
tx.create(GarySTheGreenMile)
tx.create(KevinBAFewGoodMen)
tx.create(HelenHAsGoodAsItGets)
tx.create(MegRTopGun)
tx.create(BenMSpeedRacer)
tx.create(KellyMTopGun)
tx.create(RiverPStandByMe)
tx.create(RobinWhatDreamsMayCome)
tx.create(TomHCastAway)
tx.create(OrlandoTheReplacements)
tx.create(JackNAFewGoodMen)
tx.create(CubaGAFewGoodMen)
tx.create(NoahWAFewGoodMen)
tx.create(BenMVforVendetta)
tx.create(MichaelSFrostNixon)
tx.create(MegRJoeVersustheVolcano)
tx.create(JohnCStandByMe)
tx.create(ChristianBRescueDawn)
tx.create(RosieOALeagueofTheirOwn)
tx.create(ReneeZJerryMaguire)
tx.create(GeenaDALeagueofTheirOwn)
tx.create(HelenHTwister)
tx.create(TomHTheDaVinciCode)
tx.create(ChristopherGAFewGoodMen)
tx.create(SteveZRescueDawn)
tx.create(PhilipHTwister)
tx.create(ZachGTwister)
tx.create(RichardHUnforgiven)
tx.create(StephenRVforVendetta)
tx.create(DianeKSomethingsGottaGive)
tx.create(NataliePVforVendetta)
tx.create(LivTThatThingYouDo)
tx.create(JerryOJerryMaguire)
tx.create(JTWHoffa)
tx.create(GregKYouveGotMail)
tx.create(CubaGAsGoodAsItGets)
tx.create(BillPaxApollo13)
tx.create(EdHApollo13)
tx.create(SteveZYouveGotMail)
tx.create(AnthonyETopGun)
tx.create(WilWStandByMe)
tx.create(VictorGSleeplessInSeattle)
tx.create(PhilipHCharlieWilsonsWar)
tx.create(BillyCWhenHarryMetSally)
tx.create(JackNSomethingsGottaGive)
tx.create(TomHThePolarExpress)
tx.create(JohnHVforVendetta)
tx.create(JackNHoffa)
tx.create(ValKTopGun)
tx.create(EthanHSnowFallingonCedars)
tx.create(IceTJohnnyMnemonic)
tx.create(KevinBFrostNixon)
tx.create(KevinBApollo13)
tx.create(SamRFrostNixon)
tx.create(BonnieHTheGreenMile)
tx.create(DinaJohnnyMnemonic)
tx.create(TomCJerryMaguire)
tx.create(BrunoKWhenHarryMetSally)
tx.create(TomHApollo13)
tx.create(TomHALeagueofTheirOwn)
tx.create(GeneTheReplacements)
tx.create(JuliaRCharlieWilsonsWar)
tx.create(TomHJoeVersustheVolcano)
tx.create(TomHYouveGotMail)
tx.create(MichaelDTheGreenMile)
tx.create(AlTheDevilsAdvocate)
tx.create(KeanuJohnnyMnemonic)
tx.create(JamesCSnowFallingonCedars)
tx.create(KeanuSomethingsGottaGive)
tx.create(MegRYouveGotMail)
tx.create(RickYSnowFallingonCedars)
tx.create(HelenHCastAway)
tx.create(GarySApollo13)
tx.create(DaveCYouveGotMail)
tx.create(KeanuTheDevilsAdvocate)
tx.create(LoriPALeagueofTheirOwn)
tx.create(BonnieHJerryMaguire)
tx.create(GeneUnforgiven)
tx.create(DemiMAFewGoodMen)
tx.create(JTWAFewGoodMen)
tx.create(TomCAFewGoodMen)
tx.create(KieferSAFewGoodMen)
tx.create(KevinPAFewGoodMen)
tx.create(HalleBCloudAtlas)
tx.create(AaronSAFewGoodMen)
tx.create(ReginaKJerryMaguire)
tx.create(CarrieFWhenHarryMetSally)
tx.create(DannyDOneFlewOvertheCuckoosNest)
tx.create(CharlizeTheDevilsAdvocate)
tx.create(TomCTopGun)
tx.create(PatriciaCTheGreenMile)
tx.create(JackNAsGoodAsItGets)
tx.create(NaomieHNinjaAssassin)
tx.create(SusanSSpeedRacer)
tx.create(LaurenceTheMatrix)
tx.create(LaurenceTheMatrixReloaded)
tx.create(LaurenceTheMatrixRevolutions)
tx.create(MarshallBStandByMe)
tx.create(TomHThatThingYouDo)
tx.create(MaxSSnowFallingonCedars)
tx.create(KeanuTheMatrix)
tx.create(KeanuTheMatrixReloaded)
tx.create(KeanuTheMatrixRevolutions)
tx.create(ParkerPYouveGotMail)
tx.create(TomHTheGreenMile)
tx.create(JohnRHoffa)
tx.create(JamesMAFewGoodMen)
tx.create(JohnGSpeedRacer)
tx.create(MatthewFSpeedRacer)
tx.create(RainNinjaAssassin)
tx.create(JackNOneFlewOvertheCuckoosNest)
tx.create(JonathanLJerryMaguire)
tx.create(TomHCharlieWilsonsWar)
tx.create(FrankLFrostNixon)
tx.create(DannyDHoffa)
tx.create(CubaGJerryMaguire)
tx.create(OliverPBicentennialMan)
tx.create(BenMNinjaAssassin)
tx.create(MegRWhenHarryMetSally)
tx.create(TomHSleeplessInSeattle)
tx.create(GeneTheBirdcage)
tx.create(KeanuTheReplacements)
tx.create(PaulBTheDaVinciCode)
tx.create(GregKAsGoodAsItGets)
tx.create(IanMTheDaVinciCode)
tx.create(AudreyTTheDaVinciCode)
tx.create(EmileHSpeedRacer)
tx.create(ZachGRescueDawn)
tx.create(RitaWSleeplessInSeattle)
tx.create(RainSpeedRacer)
tx.create(TakeshiJohnnyMnemonic)
tx.create(RickYNinjaAssassin)
tx.create(CoreyFStandByMe)
tx.create(WernerHWhatDreamsMayCome)
tx.create(MaxSWhatDreamsMayCome)
tx.create(CharlizeThatThingYouDo)
tx.create(CarrieTheMatrix)
tx.create(CarrieTheMatrixReloaded)
tx.create(CarrieTheMatrixRevolutions)
tx.create(ChristinaRSpeedRacer)
tx.create(HugoVforVendetta)
tx.create(JerryOStandByMe)
tx.create(TomSTopGun)
tx.create(JimBCloudAtlas)
tx.create(BillPullSleeplessInSeattle)
tx.create(JamesCTheGreenMile)
tx.create(TomHCloudAtlas)
graph.commit(tx)
