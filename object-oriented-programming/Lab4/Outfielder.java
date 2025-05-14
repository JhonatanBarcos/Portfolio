public class Outfielder extends Player {
    //no attributes

    //Constructor
    public Outfielder(boolean g, String n, int a, Country nat ){
        super(g, n, a, nat);
    }

    //methods
    public void update(Competition c, Match m){
        if(stats.containsKey(c)){
            stats.get(c).updateStats(m);
        } else {
            PlayerStats ps = new OutfielderStats(this);
            ps.updateStats(m);
            stats.put(c, ps);
            } 
        }
}


