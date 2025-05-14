import java.util.*;

public class GroupPlay extends Competition {
    //attributes
    private int noGroups;
    private LinkedList<League> groups = new LinkedList<League>();


    //constructor
    public GroupPlay(boolean cl, String n, Country c, Gender g) {
        super(cl,n,c,g);

    }

    //methods
    public void generateGroups(){
        Collections.shuffle(this.teams); 
        
        int teamsPerLeague = teams.size() / noGroups;
        int extraTeams = teams.size() % noGroups;
    
        for (int i = 0; i < teams.size(); i += teamsPerLeague) {
            LinkedList<Team> leagueTeams = new LinkedList<Team>();
            int teamsInThisLeague = teamsPerLeague;
    
            if (extraTeams > 0) {
                teamsInThisLeague++;
                extraTeams--;
            }
            for (int j = i; j < i + teamsInThisLeague && j < teams.size(); j++) {
                leagueTeams.add(teams.get(j));
            }

            String leagueName = "League " + (i / teamsPerLeague + 1);
            League league = new League(this.clubs, leagueName, this.country, this.gender);
            league.teams = leagueTeams;
            this.groups.add(league);
        }
    }

    public void printGroups(){
        System.out.println("\n========================================");
        System.out.println( "Printing " +this.name + " groups:");
        System.out.println("========================================");
        for(League league: groups){
            System.out.println("\n" + league.getName() + ":");
            for(Team team: league.getTeams()){
                System.out.println(team.getName());
            }
        }
    }

    public void generateMatches(){
        for(League league: groups){
            league.generateMatches();
        }    
    }
    


    public void simulateMatches(){
        for(League league: groups){
            league.simulateMatches();
            league.printMatches();

        }
    }
}
