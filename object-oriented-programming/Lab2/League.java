import java.util.*; 


public class League {
    //attributes

    private String name;
    private Country country;
    private LinkedList<Team> teams = new LinkedList<Team>();
    private Gender gender;
    private LinkedList<Match> matches = new LinkedList<Match>();

    // constructor
    public League(String n, Country c, Gender g) {
        this.name = n;
        this.country = c;
        this.gender = g;
    }

    // getters and setters
    public String getName() {
        return this.name;
    }

    public Country getCountry() {
        return this.country;
    }

    public Gender getGender() {
        return this.gender;
    }

    // other methods
    public boolean addTeam(Team team) {
        //Country conditions
        if (team.getCountry().equals(this.country)){
            //Gender conditions
            if((team.getGenderClass().equals(Team.Gender.Female) && this.gender.equals(League.Gender.Female)) || (team.getGenderClass().equals(Team.Gender.Male) && this.gender.equals(League.Gender.Male)) || (this.gender.equals(League.Gender.Mixed))){
                teams.add(team);
                System.out.println(team.getName() + " added to the league " + this.name);
                return true;
            } else {
                System.out.println(team.getName() + " can't be added to the league " + this.name + " cause of gender issues");
                return false;    
            }
        } else {
            System.out.println(team.getName() + " can't be added to the league " + this.name + " cause of country issues");
            return false;

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
        for (int i = 0; i < teams.size(); i++) {
            for (int j = i+1; j < teams.size(); j++) {
                Match match1 = new Match(teams.get(i), teams.get(j));
                Match match2 = new Match(teams.get(j), teams.get(i));
                this.matches.add(match1);
                this.matches.add(match2);
            }
        }
    }

    public void simulateMatches(){
        System.out.println("\n==================================");
        System.out.println("Simulating matches of " + this.name);
        System.out.println("==================================");
        for (Match match : this.matches) {
            match.simulateMatch();
            match.getHomeTeam().updateTeamStats(match);
            match.getAwayTeam().updateTeamStats(match);
        }
    }

    public void printMatches(){
        for (Match match: this.matches){
            match.printMatch();
        }
    }

    public enum Gender{Male, Female, Mixed};
}
