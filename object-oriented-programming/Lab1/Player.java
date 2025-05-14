
public class Player{
    //Atributos
    private boolean female;    
    private String name;
    private int age;
    private Country nationality;
    private int noMatches;
    private int noTackles;
    private int noPasses;
    private int noShots;
    private int noAssists;
    private int noGoals;

    //Constructor
    Player(boolean g, String n, int a, Country nat ){
        female = g;
        name = n;
        age = a;
        nationality = nat;
    }

    //Getters
    boolean isFemale(){
        return this.female;
    }
    int getAge(){
        return this.age;
    }
    String getName(){
        return this.name;
    }
    Country getNationality(){
        return this.nationality;
    }

    //Methods
    void update(int t, int p, int s, int a, int g){
        this.noTackles += t;
        this.noPasses += p;
        this.noShots += s;
        this.noAssists += a;
        this.noGoals += g;
        this.noMatches++;
    }

    void printStats(){
        System.out.println("\n" + this.name + " stats");
        System.out.println("- noMatches: " + this.noMatches);
        System.out.println("- noTrackles: " + this.noTackles);
        System.out.println("- noPasses: " + this.noPasses);
        System.out.println("- noShots: " + this.noShots);
        System.out.println("- noAssists: " + this.noAssists);
        System.out.println("- noGoals: " + this.noGoals);
        
    }
        
}