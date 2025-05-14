
public class Player{
    //Atributos
    private boolean female;    
    private String name;
    private int age;
    private Country nationality;
    private int noMatches;
    private int noTackles; //0
    private int noPasses; //0
    private int noShots; //0
    private int noAssists; //0
    private int noGoals;

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

    public void printStats(){
        System.out.println("\n" + this.name + " stats");
        System.out.println("- noMatches: " + this.noMatches);
        System.out.println("- noTrackles: " + this.noTackles);
        System.out.println("- noPasses: " + this.noPasses);
        System.out.println("- noShots: " + this.noShots);
        System.out.println("- noAssists: " + this.noAssists);
        System.out.println("- noGoals: " + this.noGoals);
        
    }
        
}