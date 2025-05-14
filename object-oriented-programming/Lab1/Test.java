
public class Test {
    public static void main(String[] args) {

        //Create country instances
        Country spain = new Country("Spain");
        Country france = new Country("France");


        //Create player instances
        Player p1 = new Player(false, "Cristiano Ronaldo", 35, spain);
        Player p2 = new Player(false, "Lionel Messi", 33, spain);
        Player p3 = new Player(false, "Sergio Ramos", 34, spain);
        Player p4 = new Player(false, "Kylian Mbappé", 21, france);
        Player p5 = new Player(false, "Neymar", 28, france);
        Player p6 = new Player(false, "Karim Benzema", 32, france);
        Player p7 = new Player(true, "Alexia Putellas", 29, spain);

        //Create team instances
        Team t1 = new Team("FC Barcelona", spain, Team.Gender.Male);
        Team t2 = new Team("PSG", france, Team.Gender.Male);

        //Add players to the teams
        t1.addPlayer(p1);
        t1.addPlayer(p2);
        t1.addPlayer(p3);
        t2.addPlayer(p4);
        t2.addPlayer(p5);
        t2.addPlayer(p6);
 
        //Print players of each team
        System.out.println("==================================");
        System.out.println("Printing players of each team");
        System.out.println("==================================");
        t1.printPlayers();
        t2.printPlayers();

        //Print teams information
        System.out.println("\n==================================");
        System.out.println("Printing info of each team");
        System.out.println("==================================");
        //info team 1
        System.out.println("Name of team 1: " + t1.getName());
        System.out.println("Country of team 1: " + t1.getCountry().getName());
        System.out.println("Gender of team 1: " + t1.getGenderClass());
        //info team 2
        System.out.println("\nName of team 2: " + t2.getName());
        System.out.println("Country of team 2: " + t2.getCountry().getName());
        System.out.println("Gender of team 2: " + t2.getGenderClass());

        //Play matches
        System.out.println("\n==================================");
        System.out.println("Printing stats of each team");
        System.out.println("==================================");
        t1.playMatch(2, 1);
        t1.playMatch(1, 1);
        t1.playMatch(0, 1);
        t2.playMatch(1, 1);
        t2.playMatch(1, 2);
        t2.playMatch(3, 1);

        //Print stats of each team
        t1.printStats();
        t2.printStats();

        //Update players stats
        p1.update(0, 0, 3, 0, 1);
        p2.update(0, 0, 2, 0, 0);
        p3.update(0, 0, 0, 0, 0);
        p4.update(0, 0, 1, 0, 0);
        p5.update(0, 0, 0, 0, 0);
        p6.update(0, 0, 0, 0, 0);

        //Print players stats
        System.out.println("\n==================================");
        System.out.println("Printing stats of each player");
        System.out.println("==================================");
        p1.printStats();
        p2.printStats();
        p3.printStats();
        p4.printStats();
        p5.printStats();
        p6.printStats();

        //Update players of teams
        t1.removePlayer(p1);
        t2.removePlayer(p4);
        t1.addPlayer(p4);
        t2.addPlayer(p1);

        //Print players of each team
        System.out.println("==================================");
        System.out.println("Printing updated players of each team");
        System.out.println("==================================");
        t1.printPlayers();
        t2.printPlayers();

        //Add Female to team 1
        System.out.println("\n==================================");
        System.out.println("Try to add a girl to team 1");
        System.out.println("==================================");

        System.out.println("\nPrinting info of player 7");
        System.out.println("- Name: " + p7.getName());
        System.out.println("- Age: " + p7.getAge());
        System.out.println("- Country: " + p7.getNationality().getName());
        if(p7.isFemale() == true){
            System.out.println("- Gender: Female" );
        } else {
            System.out.println("- Gender: Male");
        }

        t1.addPlayer(p7);
        t1.printPlayers();

        //Create a mixed team
        Team t3 = new Team("Mixed Team", spain, Team.Gender.Mixed);
        t3.addPlayer(p1);
        t3.addPlayer(p2);
        System.out.println("\n==================================");
        System.out.println("Trying to add a girl to mixed team");
        System.out.println("==================================");

        t3.addPlayer(p7);
        t3.printPlayers();
    }
}
