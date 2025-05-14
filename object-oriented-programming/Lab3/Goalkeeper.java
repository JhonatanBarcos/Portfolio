public class Goalkeeper extends Player {
    //attributes
    private int noSaves; //0
    private int noGoalsLet;

    //constructor
    public Goalkeeper(boolean g, String n, int a, Country nat ){
        super(g,n,a,nat);
    }

    //methods
    public void updatePlayerStats(Match m){
        int k = m.getHomeScorers().size();
        for(int i=0; i<k; i++){
            if (this.equals(m.getHomeScorers().get(i))){
                this.noGoalsLet++;
            }
        }

        int l = m.getAwayScorers().size();
        for(int j=0; j<l; j++){
            if (this.equals(m.getAwayScorers().get(j))){
                this.noGoalsLet++;
            }
        }

        this.noMatches++;
    }
}
