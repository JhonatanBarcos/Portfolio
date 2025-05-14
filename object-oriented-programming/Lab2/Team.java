import java.util.*;

public class Team{
    //Atributos
    private String name;
    private Country country;   
    private Gender genderClass;
    private LinkedList<Player> players;
    private int noMatches;
    private int noWins;
    private int noTies;
    private int noLosses;
    private int noGoalsScored;
    private int noGoalsReceived;

    //Constructor
    public Team(String n, Country c, Gender g){
        this.name = n;
        this.country = c;
        this.genderClass = g;
        this.players = new LinkedList<>();
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
   
    //Methods
    public void playMatch(int gs, int gr){
        if(gr>gs){
            this.noLosses = this.noLosses + 0;
        } else if(gr<gs){
            this.noWins = this.noWins + 3;
        } else {
            this.noTies = this.noTies + 1;
        }
        
        this.noGoalsScored += gs;
        this.noGoalsReceived += gr;
        this.noMatches++;
    }

    public void printStats(){
        System.out.println("\n" + this.name + " statics");
        System.out.println("- noMatches: " + this.noMatches);
        System.out.println("- noWins: " + this.noWins);
        System.out.println("- noTies: " + this.noTies);
        System.out.println("- noLosses: " + this.noLosses);
        System.out.println("- noGoalsScored: " + this.noGoalsScored);
        System.out.println("- noGoalsReceived: " + this.noGoalsReceived);
        
    }

    public void updateTeamStats(Match m){
        int k = m.getHomeTeam().getPlayers().size();
        int j = m.getAwayTeam().getPlayers().size();
        if (this.equals(m.getHomeTeam())){
            for(int i=0; i<k; i++){
                m.getHomeTeam().getPlayers().get(i).updatePlayerStats(m);
            }
            this.noGoalsScored += m.getHomeGoals();
            this.noGoalsReceived += m.getAwayGoals();
            this.noMatches++;
            if(m.getHomeGoals()>m.getAwayGoals()){
                this.noWins = this.noWins + 3;
            } else if(m.getHomeGoals()<m.getAwayGoals()){
                this.noLosses = this.noLosses + 0;
            } else {
                this.noTies = this.noTies + 1;
            }
            
        } else {
            for(int i=0; i<j; i++){
                m.getAwayTeam().getPlayers().get(i).updatePlayerStats(m);
            }
            this.noGoalsScored += m.getAwayGoals();
            this.noGoalsReceived += m.getHomeGoals();
            this.noMatches++;
            if(m.getAwayGoals()>m.getHomeGoals()){
                this.noWins = this.noWins + 3;
            } else if(m.getAwayGoals()<m.getHomeGoals()){
                this.noLosses = this.noLosses + 0;
            } else {
                this.noTies = this.noTies + 1;
            }

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

    public enum Gender{Male, Female, Mixed};
}