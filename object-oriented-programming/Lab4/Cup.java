import java.util.*; 

public class Cup extends Competition {
    //attributes
    private LinkedList<Team> tr = new LinkedList<Team>();
    private LinkedList<Match> mr = new LinkedList<Match>();
    //constructor
    public Cup(boolean cl, String n, Country c, Gender g) {
        super(cl,n,c,g);
    }
    
    //methods
    public void generateMatches() {
        Collections.shuffle(this.teams, new Random());
        tr = this.teams;
        mr = new LinkedList<Match>();
    
        while (tr.size() > 1) {
            for (int i = 0; i < tr.size(); i += 2) {
                Match match = new Match(tr.get(i), tr.get(i + 1));
                mr.add(match);
            }
            this.matches = mr;
            simulateMatches();
        }
        System.out.println("\nThe winner of " + this.getName() + " is " + teams.get(0).getName());   
    }
    
    public void simulateMatches() {
        tr = new LinkedList<Team>();
    
        for (Match match : this.matches) {
            do {
                match.simulateMatch();
            } while (match.getHomeGoals() == match.getAwayGoals());
    
            if (match.getHomeGoals() > match.getAwayGoals()) {
                tr.add(match.getHomeTeam());
            } else {
                tr.add(match.getAwayTeam());
            }
        }
        mr = new LinkedList<Match>();
        this.teams = tr;
    }


}
