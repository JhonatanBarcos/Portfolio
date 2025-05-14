
public class Player{
    //Atributos
    protected boolean female;    
    protected String name;
    protected int age;
    protected Country nationality;
    protected int noMatches;

    //Constructor
    public Player(boolean g, String n, int a, Country nat ){
        female = g;
        name = n;
        age = a;
        nationality = nat;
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
    public boolean equals(Player p){
        return this.equals(p);
    }


    public void updatePlayerStats(Match m){
        this.noMatches++;
    }

        
}