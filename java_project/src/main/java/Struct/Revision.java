package Struct;

public class Revision {
    private long id, colID;
    private String nome,timestamp;
    
    public Revision(){
        this.id = -1;
        this.colID = -1;
        this.nome = null;
        this.timestamp = null;
    }
    
    public Revision(long id, long colID, String nome, String timestamp){
        this.id = id;
        this.colID = colID;
        this.nome = nome;
        this.timestamp = timestamp;
    }
    
    public long getID(){
        return this.id;
    }
    
    public long getColID(){
        return this.colID;
    }
    
    public String getNome(){
        return this.nome;
    }
    
    public String getTimestamp(){
        return this.timestamp;
    }
    
}
