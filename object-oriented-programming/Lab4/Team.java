import java.util.*;

public class Team{
    //Atributos
    protected String name;
    protected Country country;   
    protected Gender genderClass;
    protected LinkedList<Player> players;
    protected HashMap<Competition, TeamStats> stats;

    //Constructor
    public Team(String n, Country c, Gender g){
        this.name = n;
        this.country = c;
        this.genderClass = g;
        this.players = new LinkedList<>();
        this.stats = new HashMap<Competition, TeamStats>();
    }

    //Getters
    public String getName(){
        return this.name;
    }
    public Country getCountry(){
        return this.country;
    }
    public Gender getGenderClass(){
        return this.genderClass;
    }

    public LinkedList<Player> getPlayers(){
        return this.players;
    }

    public TeamStats getStats(Competition competition){
        return this.stats.get(competition);
    }
   
    //Methods
   public void update(Competition c, Match m){
        //Check dictionary
        if(this.stats.containsKey(c)){
            this.stats.get(c).updateStats(m);
            
        } else{
            //Create new TeamStats
            TeamStats ts = new TeamStats(this);
            ts.updateStats(m);
            this.stats.put(c, ts);
        }
        //Update players
        for (Player p : this.players){
                p.update(c, m);
            }
    }


    public void printPlayers(){
        System.out.println("\nPrinting players of " + this.name);
        for(Player player : this.players){
            System.out.println("- " + player.getName());
        }
    }

    public boolean addPlayer(Player p){
        if((p.isFemale() && this.genderClass.equals(Team.Gender.Female)) || (!p.isFemale() && this.genderClass.equals(Team.Gender.Male)) || this.genderClass.equals(Team.Gender.Mixed)){
            System.out.println("\n* " + p.getName() + " added to the team " + this.name );
            this.players.add(p);
            return true;
        }
        System.out.println("\n* " + p.getName() + " can't be added to the team " + this.name + "due to gender issues");
        return false;
    }

    public boolean removePlayer(Player p){
        if((p.isFemale() && this.genderClass.equals(Team.Gender.Female)) || (!p.isFemale() && this.genderClass.equals(Team.Gender.Male)) || this.genderClass.equals(Team.Gender.Mixed)){
            System.out.println("\n* " + p.getName() + " removed of the team " + this.name );
            this.players.remove(p);
            return true;
        }
        System.out.println("\n* " + p.getName() + " can't be removed of the team " + this.name + "due to gender issues");
        return false;
    }

    public enum Gender{Male, Female, Mixed}
}