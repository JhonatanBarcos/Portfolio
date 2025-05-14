public class League extends Competition {
    //no attributes

    //constructor
    public League(boolean cl, String n, Country co, Gender g) {
        super(cl,n,co,g);
    }

    //methods
    public void generateMatches(){
        for (int i = 0; i < teams.size()-1; i++) {
            for (int j = i+1; j < teams.size(); j++) {
                Match match1 = new Match(teams.get(i), teams.get(j));
                Match match2 = new Match(teams.get(j), teams.get(i));
                this.matches.add(match1);
                this.matches.add(match2);
            }
        }
    }
}
