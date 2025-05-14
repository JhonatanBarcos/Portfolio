public class NationalTeam extends Team {
    //no attributes

    //Constructor
    public NationalTeam(String n, Country c, Gender g){
        super(n,c,g);
    }

    //Methods
    public boolean addPlayer(Player p){
        if((p.isFemale() && this.genderClass.equals(Team.Gender.Female)) || (!p.isFemale() && this.genderClass.equals(Team.Gender.Male)) || this.genderClass.equals(Team.Gender.Mixed)){
            if(country.equals(p.getNationality())){
                System.out.println("\n* " + p.getName() + " added to the team " + this.name );
                super.addPlayer(p);
                return true;                
            }
        }
        System.out.println("\n* " + p.getName() + " can't be added to the team " + this.name + "due to gender issues");
        return false;
    }
}
