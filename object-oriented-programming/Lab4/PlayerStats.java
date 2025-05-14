public abstract class PlayerStats implements Comparable<PlayerStats> {
    //attributes
    protected Player player;
    protected int noMatches;

    //Constructor
    public PlayerStats(Player p){
        this.player = p;
    }

    //methods
    public abstract void updateStats(Match m);
    public abstract void printStats();
}