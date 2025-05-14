public class Goalkeeper extends Player {
    //no attributes

    //constructor
    public Goalkeeper(boolean g, String n, int a, Country nat ){
        super(g,n,a,nat);
    }

    //methods
    public void update(Competition c, Match m){
        if(stats.containsKey(c)){
            stats.get(c).updateStats(m);
        } else {
            PlayerStats ps = new GoalkeeperStats(this);
            ps.updateStats(m);
            stats.put(c, ps);
            } 
        }
}

