public class Outfielder extends Player {
    private int noTrackles;
    private int noPasses;
    private int noShots;
    private int noAssists;
    private int noGoals;

    //Constructor
    public Outfielder(boolean g, String n, int a, Country nat ){
        super(g, n, a, nat);
    }

    //Methods
    public void updatePlayerStats(Match m){
        int k = m.getHomeScorers().size();
        for(int i=0; i<k; i++){
            if (this.equals(m.getHomeScorers().get(i))){
                this.noGoals++;
            }
        }

        int l = m.getAwayScorers().size();
        for(int j=0; j<l; j++){
            if (this.equals(m.getAwayScorers().get(j))){
                this.noGoals++;
            }
        }

        this.noMatches++;
    }
}
