public class TestClass {
    public static void main(String[] args) {

        //Create country instances
        Country spain = new Country("Spain");
        Country france = new Country("France");

        //Create player instances
        Player p1 = new Outfielder(false, "Cristiano Ronaldo", 35, spain);
        Player p2 = new Outfielder(false, "Lionel Messi", 33, spain);
        Player p3 = new Outfielder(false, "Sergio Ramos", 34, spain);
        Player p4 = new Outfielder(false, "Sergio Busquets", 33, spain);
        Player p5 = new Outfielder(false, "Gerard Piqué", 34, spain);
        Player p6 = new Outfielder(false, "Jordi Alba", 32, spain);
        Player p7 = new Outfielder(false, "Sergio Ramos", 35, spain);
        Player p8 = new Outfielder(false, "Thiago Alcântara", 30, spain);
        Player p9 = new Outfielder(false, "Koke", 29, spain);
        Player p10 = new Outfielder(false, "Álvaro Morata", 28, spain);
        Player p11 = new Goalkeeper(false, "Marco Asensio", 25, spain);

        Player p12 = new Outfielder(false, "Dani Olmo", 23, spain);
        Player p13 = new Outfielder(false, "Ferran Torres", 21, spain);
        Player p14 = new Outfielder(false, "Pedri", 18, spain);
        Player p15 = new Outfielder(false, "Santi Cazorla", 36, spain);
        Player p16 = new Outfielder(false, "David Silva", 35, spain);
        Player p17 = new Outfielder(false, "Iker Casillas", 40, spain);
        Player p18 = new Outfielder(false, "Xavi Hernández", 41, spain);
        Player p19 = new Outfielder(false, "Andrés Iniesta", 37, spain);
        Player p20 = new Outfielder(false, "Fernando Torres", 37, spain);
        Player p21 = new Outfielder(false, "Carles Puyol", 43, spain);
        Player p22 = new Outfielder(false, "Fernando Hierro", 53, spain);
        Player p23 = new Goalkeeper(false, "Raúl González", 44, spain);
        
        Player p24 = new Outfielder(false, "Kylian Mbappé", 22, france);
        Player p25 = new Outfielder(false, "Antoine Griezmann", 30, france);
        Player p26 = new Outfielder(false, "Paul Pogba", 28, france);
        Player p27 = new Outfielder(false, "Hugo Lloris", 34, france);
        Player p28 = new Outfielder(false, "Raphaël Varane", 28, france);
        Player p29 = new Outfielder(false, "Benjamin Pavard", 25, france);
        Player p30 = new Outfielder(false, "Lucas Hernández", 25, france);
        Player p31 = new Outfielder(false, "N'Golo Kanté", 30, france);
        Player p32 = new Outfielder(false, "Olivier Giroud", 34, france);
        Player p33 = new Outfielder(false, "Adrien Rabiot", 26, france);
        Player p34 = new Goalkeeper(false, "Kingsley Coman", 25, france);

        Player p35 = new Outfielder(true, "Wendie Renard", 30, france);
        Player p36 = new Outfielder(true, "Amandine Henry", 31, france);
        Player p37 = new Outfielder(true, "Eugénie Le Sommer", 32, france);
        Player p38 = new Outfielder(true, "Delphine Cascarino", 23, france);
        Player p39 = new Outfielder(true, "Sakina Karchaoui", 25, france);
        Player p40 = new Outfielder(true, "Marion Torrent", 28, france);
        Player p41 = new Outfielder(true, "Griedge Mbock Bathy", 26, france);
        Player p42 = new Outfielder(true, "Grace Geyoro", 24, france);
        Player p43 = new Outfielder(true, "Kadidiatou Diani", 26, france);
        Player p44 = new Outfielder(true, "Valérie Gauvin", 25, france);
        Player p45 = new Goalkeeper(true, "Sarah Bouhaddi", 35, france);

        Player p46 = new Outfielder(true, "Amel Majri", 28, france);
        Player p47 = new Outfielder(true, "Eve Périsset", 27, france);
        Player p48 = new Outfielder(true, "Estelle Cascarino", 24, france);
        Player p49 = new Outfielder(true, "Maéva Clemaron", 28, france);
        Player p50 = new Outfielder(true, "Charlotte Bilbault", 31, france);
        Player p51 = new Outfielder(true, "Elise Bussaglia", 36, france);
        Player p52 = new Outfielder(true, "Gaëtane Thiney", 36, france);
        Player p53 = new Outfielder(true, "Inès Jaurena", 24, france);
        Player p54 = new Outfielder(true, "Perle Morroni", 22, france);
        Player p55 = new Outfielder(true, "Sandy Baltimore", 22, france);
        Player p56 = new Goalkeeper(true, "Viviane Asseyi", 27, france);

        Player p57 = new Outfielder(true, "Valérie Gauvin", 25, france);
        Player p58 = new Outfielder(true, "Sarah Bouhaddi", 35, france);
        Player p59 = new Outfielder(true, "Aïssatou Tounkara", 25, france);
        Player p60 = new Outfielder(true, "Elisa De Almeida", 25, france);
        Player p61 = new Outfielder(true, "Eugénie Le Sommer", 32, france);
        Player p62 = new Outfielder(true, "Delphine Cascarino", 23, france);
        Player p63 = new Outfielder(true, "Sakina Karchaoui", 25, france);
        Player p64 = new Outfielder(true, "Marion Torrent", 28, france);
        Player p65 = new Outfielder(true, "Griedge Mbock Bathy", 26, france);
        Player p66 = new Outfielder(true, "Grace Geyoro", 24, france);
        Player p67 = new Goalkeeper(true, "Kadidiatou Diani", 26, france);


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


        //Create diferent types of competitions
        //1. League
        System.out.println("\n==================================");
        System.out.println("Create League based on Competition");
        System.out.println("==================================");
        Competition league = new League(true, "League Competition", france, Competition.Gender.Mixed);
        league.addTeam(spainMaleTeam1);
        league.addTeam(franceMaleTeam);
        league.addTeam(franceFemaleTeam1);
        league.addTeam(franceFemaleTeam2);
        league.addTeam(franceFemaleTeam3);

        league.generateMatches();
        league.simulateMatches();
        
        league.printTable();

        league.printGoalScorers(3); 
    }
}
/* 
        //2. GroupPlay
        System.out.println("\n==================================");
        System.out.println("Create GroupPlay based on Competition");
        System.out.println("==================================");

        GroupPlay groupPlay = new GroupPlay(true, "GroupPlay Competition", france, Competition.Gender.Mixed);
        groupPlay.addTeam(spainMaleTeam1);
        groupPlay.addTeam(franceMaleTeam);
        groupPlay.addTeam(franceFemaleTeam1);
        groupPlay.addTeam(franceFemaleTeam2);
        groupPlay.addTeam(franceFemaleTeam3);

        groupPlay.generateGroups();
        groupPlay.printGroups();
        groupPlay.generateMatches();
        groupPlay.simulateMatches();
        groupPlay.printMatches();
        



        //3. Cup
        System.out.println("\n==================================");
        System.out.println("Create Cup based on Competition");
        System.out.println("==================================");

        Cup cup = new Cup(true, "Cup Competition", france, Competition.Gender.Mixed);
        cup.addTeam(spainMaleTeam1);
        cup.addTeam(franceMaleTeam);
        cup.addTeam(franceFemaleTeam1);
        cup.addTeam(franceFemaleTeam2);
        cup.addTeam(franceFemaleTeam3);

        cup.generateMatches();
        

    }
    */


