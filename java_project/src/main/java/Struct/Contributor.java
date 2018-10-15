package Struct;

public class Contributor {
    private long colID;
    private int nCont;
    private String nome;
    
    public Contributor(){
        this.colID = -1;
        this.nCont = -1;
        this.nome = null;
    }
    
    public Contributor(long colID, String nome){
        this.colID = colID;
        this.nCont = 1;
        this.nome = nome;
    }
    
    public long getColID(){
        return this.colID;
    }
    
    public int getNCont(){
        return this.nCont;
    }
    
    public String getNome(){
        return this.nome;
    }
    
    public void setContributions(int n){
        this.nCont = n;
    }
    
}
