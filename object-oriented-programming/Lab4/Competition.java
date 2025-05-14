import java.util.*; 


public class Competition {
    //attributes

    protected boolean clubs;
    protected String name;
    protected Country country;
    protected Gender gender;    
    protected LinkedList<Team> teams = new LinkedList<Team>();
    protected LinkedList<Match> matches = new LinkedList<Match>();

    // constructor
    public Competition(boolean cl, String n, Country co, Gender g) {
        this.clubs = cl;
        this.name = n;
        this.country = co;
        this.gender = g;
    }

    // getters and setters
    public String getName() {
        return this.name;
    }

    public boolean isClubs() {
        return this.clubs;
    }

    public Country getCountry() {
        return this.country;
    }

    public Gender getGender() {
        return this.gender;
    }

    public LinkedList<Team> getTeams() {
        return this.teams;
    }

    public LinkedList<Match> getMatches() {
        return this.matches;
    }

    public LinkedList<Player> getPlayers(){
        LinkedList<Player> players = new LinkedList<Player>();
        for (Team team : this.teams) {
            for (Player player : team.getPlayers()) {
                players.add(player);
            }
        }
        return players;
    }

    public void printTable() {
        // Defined in League
    }

    // other methods
    public boolean addTeam(Team team) {
        //Country conditions
        if(clubs==true){
            //Teams are Nationals teams**

            if (this.country.equals(team.getCountry())){
            //Gender conditions
                if((team.getGenderClass().equals(Team.Gender.Female) && this.gender.equals(League.Gender.Female)) || (team.getGenderClass().equals(Team.Gender.Male) && this.gender.equals(League.Gender.Male)) || (this.gender.equals(League.Gender.Mixed))){
                    teams.add(team);
                    System.out.println(team.getName() + " added to the competition " + this.name);
                    return true;
                } else {
                    System.out.println(team.getName() + " can't be added to the competition " + this.name + " cause of gender issues");
                    return false;
                }
            } else {
            System.out.println(team.getName() + " can't be added to the competition " + this.name + " cause of country issues");
            return false;
            }
        } else {
            //Country conditions
            if (this.country.equals(team.getCountry())){
                System.out.println(team.getName() + " can't be added to the competition " + this.name + " cause of country issues");
                return false;
            } else {
            //Gender conditions
                if((team.getGenderClass().equals(Team.Gender.Female) && this.gender.equals(League.Gender.Female)) || (team.getGenderClass().equals(Team.Gender.Male) && this.gender.equals(League.Gender.Male)) || (this.gender.equals(League.Gender.Mixed))){
                    teams.add(team);
                    System.out.println(team.getName() + " added to the competition " + this.name);
                    return true;
                } else {
                    System.out.println(team.getName() + " can't be added to the competition " + this.name + " cause of gender issues");
                    return false;    
                }
            }
        }
    }
        
    

    public boolean removeTeam(Team team) {
        //Country conditions
        if (team.getCountry().equals(this.country)){
            //Gender conditions
            if((team.getGenderClass().equals(Team.Gender.Female) && this.gender.equals(League.Gender.Female)) || (team.getGenderClass().equals(Team.Gender.Male) && this.gender.equals(League.Gender.Male)) || (this.gender.equals(League.Gender.Mixed))){
                teams.remove(team);
                System.out.println(team.getName() + " removed of the league " + this.name);
                return true;
            } else {
                System.out.println(team.getName() + " can't be removed to the league " + this.name + " cause of gender issues");
                return false;    
            }
        } else {
            System.out.println(team.getName() + " can't be removed to the league " + this.name + " cause of country issues");
            return false;
        }
    
    }

    public void generateMatches(){
       //void
    }

    public void simulateMatches(){
        System.out.println("\n==================================");
        System.out.println("Simulating matches of " + this.name);
        System.out.println("==================================");
        for (Match match : this.matches) {
            match.simulateMatch();
            match.getHomeTeam().update(this,match);
            match.getAwayTeam().update(this,match);
        }
    }

    public void printMatches(){
        for (Match match: this.matches){
            match.printMatch();
        }
    }



    public void printGoalScorers(int k){
        System.out.println("\n==================================");
        System.out.println("Printing top " + k + " scorers of " + this.name);
        System.out.println("==================================");


        //Create a list of OutfielderStats
        LinkedList<PlayerStats> playerStats = new LinkedList<PlayerStats>();

        for (Team team : this.teams) {
            for (Player player : team.getPlayers()) {
                if (player instanceof Outfielder) {
                    PlayerStats stats = (OutfielderStats) player.getStats(this);
                    playerStats.add(stats);
                }
            }
        }

        //Sort stats
        Collections.sort(playerStats);

        //Print top scorers
        for(int i=0;i<k;i++){
            playerStats.get(i).printStats();
        }
    }

    public enum Gender{Male, Female, Mixed};
}
