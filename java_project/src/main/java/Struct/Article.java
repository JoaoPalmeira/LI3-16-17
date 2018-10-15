package Struct;

public class Article {
    private long id, nwords, nchar;
    private String titulo;
    private int dups;
    
    public Article(){
        this.id = -1;
        this.nwords = -1;
        this.nchar = -1;
        this.titulo = null;
        this.dups = 0;
    }
    
    public Article(long id, long nw, long nc, String titulo){
        this.id = id;
        this.nwords = nw;
        this.nchar = nc;
        this.titulo = titulo;
        this.dups = 1;
    }
    public Article(Article a){
    	this.id = a.getID();
        this.nwords = a.getNWords();
        this.nchar = a.getNChar();
        this.titulo = a.getTitulo();
        this.dups = a.getDups();
    
    }
    
    public long getID(){
        return this.id;
    }
    
    public long getNWords(){
        return this.nwords;
    }
    
    public long getNChar(){
        return this.nchar;
    }
    
    public String getTitulo(){
        return this.titulo;
    }
    
    public int getDups(){
    	return this.dups;
    }
    public void setId(long id) {
        this.id = id;
    }
    
    public void setNwords(long nwords) {
        this.nwords = nwords;
    }
    
    public void setNchar(long nchar) {
        this.nchar = nchar;
    }
    public void setDups(int n){
    	this.dups = n;
    }
    public void setTitulo(String titulo) {
        this.titulo = titulo;
    }
    
    public void novoDuplicado(){
    	this.dups ++;
    }
    public Article clone(){
    	return new Article(this);
    }
}
