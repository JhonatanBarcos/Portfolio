public class OutfielderStats extends PlayerStats{
    //attributes
    private int noTrackles;
    private int noPasses;
    private int noShots;
    private int noAssists;
    private int noGoals;

    //Constructor
    public OutfielderStats(Player p){
        super(p);
    }

    @Override
    public void updateStats(Match m){
        int k = m.getHomeScorers().size();
        for(int i=0; i<k; i++){
            if (this.player.equals(m.getHomeScorers().get(i))){
                this.noGoals++;
            }
        }

        int l = m.getAwayScorers().size();
        for(int j=0; j<l; j++){
            if (this.player.equals(m.getAwayScorers().get(j))){
                this.noGoals++;
            }
        }
        this.noMatches++;
    }

    @Override
    public int compareTo(PlayerStats ps){
        if(ps instanceof OutfielderStats){
            OutfielderStats os = (OutfielderStats)ps;
            if(this.noGoals > os.noGoals){
                return -1;  
            } if (this.noGoals < os.noGoals){
                return 1;  
            } else {
                return 0;
            }
        }
        return 0; 
    }

    public void printStats(){
        System.out.println("\nPrinting stats of player: " + this.player.getName() + " from " + this.player.getNationality().getName());
        System.out.println("Number of goals: " + this.noGoals);
        System.out.println("Number of assists: " + this.noAssists);
        System.out.println("Number of shots: " + this.noShots);
        System.out.println("Number of passes: " + this.noPasses);
        System.out.println("Number of trackles: " + this.noTrackles);
    }

}


