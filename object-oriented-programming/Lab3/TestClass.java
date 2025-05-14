public class TestClass {
    public static void main(String[] args) {

        //Create country instances
        Country spain = new Country("Spain");
        Country france = new Country("France");

        //Create player instances
        Player p1 = new Player(false, "Cristiano Ronaldo", 35, spain);
        Player p2 = new Player(false, "Lionel Messi", 33, spain);
        Player p3 = new Player(false, "Sergio Ramos", 34, spain);
        Player p4 = new Player(false, "Sergio Busquets", 33, spain);
        Player p5 = new Player(false, "Gerard Piqué", 34, spain);
        Player p6 = new Player(false, "Jordi Alba", 32, spain);
        Player p7 = new Player(false, "Sergio Ramos", 35, spain);
        Player p8 = new Player(false, "Thiago Alcântara", 30, spain);
        Player p9 = new Player(false, "Koke", 29, spain);
        Player p10 = new Player(false, "Álvaro Morata", 28, spain);
        Player p11 = new Player(false, "Marco Asensio", 25, spain);

        Player p12 = new Player(false, "Dani Olmo", 23, spain);
        Player p13 = new Player(false, "Ferran Torres", 21, spain);
        Player p14 = new Player(false, "Pedri", 18, spain);
        Player p15 = new Player(false, "Santi Cazorla", 36, spain);
        Player p16 = new Player(false, "David Silva", 35, spain);
        Player p17 = new Player(false, "Iker Casillas", 40, spain);
        Player p18 = new Player(false, "Xavi Hernández", 41, spain);
        Player p19 = new Player(false, "Andrés Iniesta", 37, spain);
        Player p20 = new Player(false, "Fernando Torres", 37, spain);
        Player p21 = new Player(false, "Carles Puyol", 43, spain);
        Player p22 = new Player(false, "Fernando Hierro", 53, spain);
        Player p23 = new Player(false, "Raúl González", 44, spain);
        
        Player p24 = new Player(false, "Kylian Mbappé", 22, france);
        Player p25 = new Player(false, "Antoine Griezmann", 30, france);
        Player p26 = new Player(false, "Paul Pogba", 28, france);
        Player p27 = new Player(false, "Hugo Lloris", 34, france);
        Player p28 = new Player(false, "Raphaël Varane", 28, france);
        Player p29 = new Player(false, "Benjamin Pavard", 25, france);
        Player p30 = new Player(false, "Lucas Hernández", 25, france);
        Player p31 = new Player(false, "N'Golo Kanté", 30, france);
        Player p32 = new Player(false, "Olivier Giroud", 34, france);
        Player p33 = new Player(false, "Adrien Rabiot", 26, france);
        Player p34 = new Player(false, "Kingsley Coman", 25, france);

        Player p35 = new Player(true, "Wendie Renard", 30, france);
        Player p36 = new Player(true, "Amandine Henry", 31, france);
        Player p37 = new Player(true, "Eugénie Le Sommer", 32, france);
        Player p38 = new Player(true, "Delphine Cascarino", 23, france);
        Player p39 = new Player(true, "Sakina Karchaoui", 25, france);
        Player p40 = new Player(true, "Marion Torrent", 28, france);
        Player p41 = new Player(true, "Griedge Mbock Bathy", 26, france);
        Player p42 = new Player(true, "Grace Geyoro", 24, france);
        Player p43 = new Player(true, "Kadidiatou Diani", 26, france);
        Player p44 = new Player(true, "Valérie Gauvin", 25, france);
        Player p45 = new Player(true, "Sarah Bouhaddi", 35, france);

        Player p46 = new Player(true, "Amel Majri", 28, france);
        Player p47 = new Player(true, "Eve Périsset", 27, france);
        Player p48 = new Player(true, "Estelle Cascarino", 24, france);
        Player p49 = new Player(true, "Maéva Clemaron", 28, france);
        Player p50 = new Player(true, "Charlotte Bilbault", 31, france);
        Player p51 = new Player(true, "Elise Bussaglia", 36, france);
        Player p52 = new Player(true, "Gaëtane Thiney", 36, france);
        Player p53 = new Player(true, "Inès Jaurena", 24, france);
        Player p54 = new Player(true, "Perle Morroni", 22, france);
        Player p55 = new Player(true, "Sandy Baltimore", 22, france);
        Player p56 = new Player(true, "Viviane Asseyi", 27, france);

        Player p57 = new Player(true, "Valérie Gauvin", 25, france);
        Player p58 = new Player(true, "Sarah Bouhaddi", 35, france);
        Player p59 = new Player(true, "Aïssatou Tounkara", 25, france);
        Player p60 = new Player(true, "Elisa De Almeida", 25, france);
        Player p61 = new Player(true, "Eugénie Le Sommer", 32, france);
        Player p62 = new Player(true, "Delphine Cascarino", 23, france);
        Player p63 = new Player(true, "Sakina Karchaoui", 25, france);
        Player p64 = new Player(true, "Marion Torrent", 28, france);
        Player p65 = new Player(true, "Griedge Mbock Bathy", 26, france);
        Player p66 = new Player(true, "Grace Geyoro", 24, france);
        Player p67 = new Player(true, "Kadidiatou Diani", 26, france);
        Player p68 = new Player(true, "Valérie Gauvin", 25, france);


        // Create the Spain Male Team and add the players to the team
        Team spainMaleTeam1 = new Team("Spain Male Team 1", spain, Team.Gender.Male);
        spainMaleTeam1.addPlayer(p1);
        spainMaleTeam1.addPlayer(p2);
        spainMaleTeam1.addPlayer(p3);
        spainMaleTeam1.addPlayer(p4);
        spainMaleTeam1.addPlayer(p5);
        spainMaleTeam1.addPlayer(p6);
        spainMaleTeam1.addPlayer(p7);
        spainMaleTeam1.addPlayer(p8);
        spainMaleTeam1.addPlayer(p9);
        spainMaleTeam1.addPlayer(p10);
        spainMaleTeam1.addPlayer(p11);

        Team spainMaleTeam2 = new Team("Spain Male Team 2", spain, Team.Gender.Male);
        spainMaleTeam2.addPlayer(p12);
        spainMaleTeam2.addPlayer(p13);
        spainMaleTeam2.addPlayer(p14);
        spainMaleTeam2.addPlayer(p15);
        spainMaleTeam2.addPlayer(p16);
        spainMaleTeam2.addPlayer(p17);
        spainMaleTeam2.addPlayer(p18);
        spainMaleTeam2.addPlayer(p19);
        spainMaleTeam2.addPlayer(p20);
        spainMaleTeam2.addPlayer(p21);
        spainMaleTeam2.addPlayer(p22);
        spainMaleTeam2.addPlayer(p23);

        //Create Male France Team
        Team franceMaleTeam = new Team("France Male Team", france, Team.Gender.Male);
        franceMaleTeam.addPlayer(p24);
        franceMaleTeam.addPlayer(p25);
        franceMaleTeam.addPlayer(p26);
        franceMaleTeam.addPlayer(p27);
        franceMaleTeam.addPlayer(p28);
        franceMaleTeam.addPlayer(p29);
        franceMaleTeam.addPlayer(p30);
        franceMaleTeam.addPlayer(p31);
        franceMaleTeam.addPlayer(p32);
        franceMaleTeam.addPlayer(p33);
        franceMaleTeam.addPlayer(p34);

        // Create the France Female Team 
        Team franceFemaleTeam1 = new Team("France Female Team 1", france, Team.Gender.Female);
        franceFemaleTeam1.addPlayer(p35);
        franceFemaleTeam1.addPlayer(p36);
        franceFemaleTeam1.addPlayer(p37);
        franceFemaleTeam1.addPlayer(p38);
        franceFemaleTeam1.addPlayer(p39);
        franceFemaleTeam1.addPlayer(p40);
        franceFemaleTeam1.addPlayer(p41);
        franceFemaleTeam1.addPlayer(p42);
        franceFemaleTeam1.addPlayer(p43);
        franceFemaleTeam1.addPlayer(p44);
        franceFemaleTeam1.addPlayer(p45);

        Team franceFemaleTeam2 = new Team("France Female Team 2", france, Team.Gender.Female);
        franceFemaleTeam2.addPlayer(p46);
        franceFemaleTeam2.addPlayer(p47);
        franceFemaleTeam2.addPlayer(p48);
        franceFemaleTeam2.addPlayer(p49);
        franceFemaleTeam2.addPlayer(p50);
        franceFemaleTeam2.addPlayer(p51);
        franceFemaleTeam2.addPlayer(p52);
        franceFemaleTeam2.addPlayer(p53);
        franceFemaleTeam2.addPlayer(p54);
        franceFemaleTeam2.addPlayer(p55);
        franceFemaleTeam2.addPlayer(p56);

        Team franceFemaleTeam3 = new Team("France Female Team 3", france, Team.Gender.Female);
        franceFemaleTeam3.addPlayer(p57);
        franceFemaleTeam3.addPlayer(p58);
        franceFemaleTeam3.addPlayer(p59);
        franceFemaleTeam3.addPlayer(p60);
        franceFemaleTeam3.addPlayer(p61);
        franceFemaleTeam3.addPlayer(p62);
        franceFemaleTeam3.addPlayer(p63);
        franceFemaleTeam3.addPlayer(p64);
        franceFemaleTeam3.addPlayer(p65);
        franceFemaleTeam3.addPlayer(p66);
        franceFemaleTeam3.addPlayer(p67);

 
        //Create competition instances
        System.out.println("\n==================================");
        System.out.println("Create Mixed National France Competition");
        System.out.println("==================================");
        Competition mxFrNatCmt = new Competition(true, "Mixed National France Competition", france, Competition.Gender.Mixed);
        mxFrNatCmt.addTeam(spainMaleTeam1);
        mxFrNatCmt.addTeam(franceMaleTeam);
        mxFrNatCmt.addTeam(franceFemaleTeam1);
        mxFrNatCmt.addTeam(franceFemaleTeam2);
        mxFrNatCmt.addTeam(franceFemaleTeam3);




        //Create diferent types of competitions
        //1. League
        System.out.println("\n==================================");
        System.out.println("Create League based on Competition");
        System.out.println("==================================");
        League league = new League(mxFrNatCmt.clubs,"League",mxFrNatCmt.country,mxFrNatCmt.gender);
        for(Team team : mxFrNatCmt.getTeams()){
            league.addTeam(team);
        }

        league.generateMatches();
        league.simulateMatches();
        league.printMatches();



        //2. GroupPlay
        System.out.println("\n==================================");
        System.out.println("Create GroupPlay based on Competition");
        System.out.println("==================================");
        GroupPlay groupPlay = new GroupPlay(mxFrNatCmt.clubs,"Group Play",mxFrNatCmt.country,mxFrNatCmt.gender);
        for(Team team : mxFrNatCmt.getTeams()){
            groupPlay.addTeam(team);
        }
        groupPlay.generateGroups();
        groupPlay.printGroups();
        groupPlay.generateMatches();
        groupPlay.simulateMatches();
        groupPlay.printMatches();
        



        //3. Cup
        System.out.println("\n==================================");
        System.out.println("Create Cup based on Competition");
        System.out.println("==================================");

        Cup cup = new Cup(mxFrNatCmt.clubs,"World Cup",mxFrNatCmt.country,mxFrNatCmt.gender);
        for(Team team : mxFrNatCmt.getTeams()){
            cup.addTeam(team);
        }
        cup.generateMatches();
        

    }
}

