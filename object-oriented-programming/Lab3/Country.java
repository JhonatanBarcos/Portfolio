public class Country {
    //Attributes
    private String name;

    //Methods
    public Country(String n) {
        this.name = n;
    }

    public String getName() {
        return this.name;
    }
    public boolean equals(Object o){
        if (o instanceof Country){
            Country c = (Country)o;
            return name == c.name;
        }
        else return false;
    }
}