import java.util.LinkedList;
import java.util.Random;

public class Match {
    //atributes
    protected Team homeTeam;
    protected Team awayTeam;
    protected int homeGoals;
    protected int awayGoals;
    protected LinkedList<Player> homeScorers = new LinkedList<Player>();
    protected LinkedList<Player> awayScorers = new LinkedList<Player>();

    //constructor
    public Match(Team h, Team a) {
        this.homeTeam = h;
        this.awayTeam = a;
    }

    //getters
    public Team getHomeTeam() {
        return this.homeTeam;
    }

    public Team getAwayTeam() {
        return this.awayTeam;
    }

    public int getHomeGoals() {
        return this.homeGoals;
    }

    public int getAwayGoals() {
        return this.awayGoals;
    }

    public LinkedList<Player> getHomeScorers() {
        return this.homeScorers;
    }

    public LinkedList<Player> getAwayScorers(){
        return this.awayScorers;
    }

    public void simulateMatch(){
        System.out.println("\n" + "Simulating match between " + this.homeTeam.getName() + " and " + this.awayTeam.getName());
        //Generate random goals
        int n = 6;
        Random random = new Random();
        this.homeGoals = random.nextInt(n);
        this.awayGoals = random.nextInt(n);

        //Print winner
        if(this.homeGoals > this.awayGoals){
            System.out.println("The winner of the match is " + this.homeTeam.getName());
        }else if(this.homeGoals < this.awayGoals){
            System.out.println("The winner of the match is " + this.awayTeam.getName());
        }else{
            System.out.println("The match ended in a draw");
        }

       //Generate random scorers
        int k = this.homeTeam.getPlayers().size();
        int j = this.awayTeam.getPlayers().size();
        for(int i=0; i<this.homeGoals; i++){
            int r = random.nextInt(k);
            this.homeScorers.add(this.homeTeam.getPlayers().get(r));
        }
        for(int i=0; i<this.awayGoals; i++){
            int r = random.nextInt(j);
            this.awayScorers.add(this.awayTeam.getPlayers().get(r));
        }

    }
    
    public void printMatch(){
        System.out.println("\n" + " Match simulated statics");
        System.out.println("- Home team: " + this.homeTeam.getName());
        System.out.println("- Away team: " + this.awayTeam.getName());
        System.out.println("- noHomeGoals: " + this.homeGoals);
        System.out.println("- noAwayGoals: " + this.awayGoals);
    }
}
