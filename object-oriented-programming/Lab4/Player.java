import java.util.*;

public class Player{
    //Atributos
    protected boolean female;    
    protected String name;
    protected int age;
    protected Country nationality;
    protected int noMatches;
    protected HashMap<Competition, PlayerStats> stats;

    //Constructor
    public Player(boolean g, String n, int a, Country nat ){
        this.female = g;
        this.name = n;
        this.age = a;
        this.nationality = nat;
        this.stats = new HashMap<Competition, PlayerStats>();
    }

    //Getters
    public boolean isFemale(){
        return this.female;
    }
    public int getAge(){
        return this.age;
    }
    public String getName(){
        return this.name;
    }
    public Country getNationality(){
        return this.nationality;
    }

    //Methods
    public void update(Competition c, Match m){
         /* 
        if(stats.containsKey(c)){
            stats.get(c).updateStats(m);
        } else {
            //Check if player is a goalkeeper or an outfielder
            if (this instanceof Outfielder){
                PlayerStats ps = new OutfielderStats(this);
                ps.updateStats(m);
                stats.put(c, ps);
            } else if (this instanceof Goalkeeper){
                PlayerStats ps = new GoalkeeperStats(this);
                ps.updateStats(m);
                stats.put(c, ps);
            } else {
                throw new IllegalArgumentException("Cannot create PlayerStats for " + this.getClass().getName());
            }
        }
        */
        
    }

    public PlayerStats getStats(Competition c){
        if (stats.containsKey(c)){
            return this.stats.get(c);
        } else {
            throw new IllegalArgumentException("Player " + this.name + " has no stats for " + c.getName());
        }
    }

    /* 
    public boolean equals(Player p){
        return this.equals(p);
    }
*/
        
}