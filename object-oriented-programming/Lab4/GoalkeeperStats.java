public class GoalkeeperStats extends PlayerStats {
    //attributes
    private int noSaves;
    private int noGoalsLet;

    //Constructor
    public GoalkeeperStats(Player p){
        super(p);
    }

    public void updateStats(Match m){
        int k = m.getHomeScorers().size();
        for(int i=0; i<k; i++){
            if (this.player.equals(m.getHomeScorers().get(i))){
                this.noGoalsLet++;
            }
        }

        int l = m.getAwayScorers().size();
        for(int j=0; j<l; j++){
            if (this.player.equals(m.getAwayScorers().get(j))){
                this.noGoalsLet++;
            }
        }
        this.noMatches++;
    }

    public void printStats(){
        System.out.println("\nPrinting stats of player: " + this.player.getName() + " from " + this.player.getNationality().getName());
        System.out.println("Number of goals: " + this.noGoalsLet);
        System.out.println("Number of saves: " + this.noSaves);
    }

    public int compareTo(PlayerStats ps){
        if(ps instanceof GoalkeeperStats){
            GoalkeeperStats os = (GoalkeeperStats)ps;
            if(this.noSaves > os.noSaves){
                return 1;
            } else if (this.noSaves < os.noSaves){
                return -1;
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    }
}