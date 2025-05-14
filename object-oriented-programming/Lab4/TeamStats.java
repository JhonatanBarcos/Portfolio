
public class TeamStats implements Comparable<TeamStats> {

    // attributes
    protected Team team;
    protected int noMatches;
    protected int noWins;
    protected int noTies;
    protected int noLosses;
    protected int noGoalsScored;
    protected int noGoalsReceived;

    //Constructor
    public TeamStats(Team t){
        this.team = t;
    }

    //methods
    public void updateStats(Match m){
        if (this.team.equals(m.getHomeTeam())){
            this.noGoalsScored += m.getHomeGoals();
            this.noGoalsReceived += m.getAwayGoals();
            this.noMatches++;
            if(m.getHomeGoals()>m.getAwayGoals()){
                this.noWins = this.noWins + 1;
            } else if(m.getHomeGoals()<m.getAwayGoals()){
                this.noLosses = this.noLosses + 1;
            } else {
                this.noTies = this.noTies + 1;
            }
            
        } else {
            this.noGoalsScored += m.getAwayGoals();
            this.noGoalsReceived += m.getHomeGoals();
            this.noMatches++;
            if(m.getAwayGoals()>m.getHomeGoals()){
                this.noWins = this.noWins + 1;
            } else if(m.getAwayGoals()<m.getHomeGoals()){
                this.noLosses = this.noLosses + 1;
            } else {
                this.noTies = this.noTies + 1;
            }

        }
    }

    public void printStats(){
        System.out.println("\nPrinting stats of " + this.team.getName());
        System.out.println("Matches: " + this.noMatches);
        System.out.println("Wins: " + this.noWins);
        System.out.println("Ties: " + this.noTies);
        System.out.println("Losses: " + this.noLosses);
        System.out.println("Goals Scored: " + this.noGoalsScored);
        System.out.println("Goals Received: " + this.noGoalsReceived);
    }

    public int compareTo(TeamStats ts){
        if ((3*this.noWins+this.noTies) > (3*ts.noWins+ts.noTies)){
            return 1;
        } else if ((3*this.noWins+this.noTies) < (3*ts.noWins+ts.noTies)){
            return -1;
        } else {
            if (this.noGoalsScored-this.noGoalsReceived > ts.noGoalsScored-ts.noGoalsReceived){
                return 1;
            } else if (this.noGoalsScored-this.noGoalsReceived < ts.noGoalsScored-ts.noGoalsReceived){
                return -1;
            } else {
                if (this.noGoalsScored > ts.noGoalsScored){
                    return 1;
                } else if (this.noGoalsScored < ts.noGoalsScored){
                    return -1;
                } else {
                    return 0;
                }
            }
        }
    }


}
