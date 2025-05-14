import java.util.*;

    public class League extends Competition {
    //no attributes

    //constructor
    public League(boolean cl, String n, Country co, Gender g) {
        super(cl,n,co,g);
    }

    //methods
    public void generateMatches(){
        for (int i = 0; i < teams.size()-1; i++) {
            for (int j = i+1; j < teams.size(); j++) {
                Match match1 = new Match(teams.get(i), teams.get(j));
                Match match2 = new Match(teams.get(j), teams.get(i));
                this.matches.add(match1);
                this.matches.add(match2);
            }
        }
    }

    public void printTable(){
        System.out.println("\n=============================");
        System.out.println("Printing table of " + this.name);
        System.out.println("=============================");

        //Create list of Team Stats
        LinkedList<TeamStats> stats = new LinkedList<>();

        //Fill stats
        for (Team t: teams){
            stats.add(t.getStats(this));
        }

        //Sort stats
        Collections.sort(stats);

        //Print table of stats
        for(TeamStats ts: stats){
            ts.printStats();
        }
    }
}
    

