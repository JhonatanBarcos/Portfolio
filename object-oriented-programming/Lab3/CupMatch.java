import java.util.Random;

public class CupMatch extends Match {
    //no attributes

    //methods
    public CupMatch(Team h, Team a) {
        super(h,a);
    }

    public void simulateMatch(){
        System.out.println("\n" + "Simulating match between " + this.homeTeam.getName() + " and " + this.awayTeam.getName());
    
        //Generate random goals
        int n = 6;
        Random random = new Random();
        this.homeGoals = random.nextInt(n);
        this.awayGoals = random.nextInt(n);
    
        //Generate random scorers
        int k = this.homeTeam.getPlayers().size();
        int j = this.awayTeam.getPlayers().size();
        
        for(int i=0; i<this.homeGoals; i++){
            int r = random.nextInt(k);
            this.homeScorers.add(this.homeTeam.getPlayers().get(r));
        }
        for(int i=0; i<this.awayGoals; i++){
            int r = random.nextInt(j);
            this.awayScorers.add(this.awayTeam.getPlayers().get(r));
        }
    
        // Keep simulating until one team scores more goals
        while (this.homeGoals == this.awayGoals) {
            if (random.nextBoolean()) {
                this.homeGoals++;
                int r = random.nextInt(k);
                this.homeScorers.add(this.homeTeam.getPlayers().get(r));
            } else {
                this.awayGoals++;
                int r = random.nextInt(j);
                this.awayScorers.add(this.awayTeam.getPlayers().get(r));
            }
        }
    }
}
