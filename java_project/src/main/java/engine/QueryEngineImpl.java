package engine;

import li3.Interface;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.stream.Collectors;

import javax.xml.stream.XMLEventReader;
import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamConstants;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.events.Characters;
import javax.xml.stream.events.EndElement;
import javax.xml.stream.events.StartElement;
import javax.xml.stream.events.XMLEvent;

import Struct.Article;
import Struct.Contributor;
import Struct.Revision;
public class QueryEngineImpl implements Interface {

	private HashMap<Long,Article> hashArts; 
	private HashMap<Long,Revision> hashRevs;
	private HashMap<Long,Contributor> hashConts;
    
	/*
	 * Inicializa a estrutura.
	 * @see li3.Interface#init()
	 */
	public void init(){
		this.hashArts = new HashMap<Long,Article>();
		this.hashRevs = new HashMap<Long,Revision>();
		this.hashConts = new HashMap<Long,Contributor>();
    }
	
	/*
	 * Método de contar palavras para a inserção durante o Load.
	 */
	public static long countWords(String s){
		long words = 0;
		char[] text = s.toCharArray();
		boolean lastspace  = false;
		if(text[0] == '\0') return 0;
		for(char c: text){
			if(c == ' ' || c == '\0'  || c == '\n' || c == '\t'){
				if(!lastspace){ 
					words ++;
					lastspace = true;
				}
			} else lastspace = false;
		}
		return words;
		
	}
	
	/*
	 * Função que faz o parsing de todos os snapshots.
	 * @see li3.Interface#load(int, java.util.ArrayList)
	 */
    public void load(int nsnaps, ArrayList<String> snaps_paths) {
    	boolean pageTitle = false;
        boolean idArtigo = false;
        boolean revisionId = false;
        boolean revisionTimestamp = false;
        boolean contriUser = false;
        boolean contriId = false;
        boolean revText = false;
        boolean revision = false;
        boolean contributor = false;
        boolean ip = false;
        boolean repRev = false;
        String title = null;
        String revTs = null;
        String ctName = null;
        Long idL = null;
        Long revIdL = null;
        Long ctIdL = null;
        long id = 0,revTextWords = 0, revId= 0, ctId = 0,revTextSize = 0;
    	
        Iterator<String> it = snaps_paths.iterator();
    	
    	while(it.hasNext()){
            //1 ciclo = 1 snapshot.
            try {
                XMLInputFactory factory = XMLInputFactory.newInstance();
                factory.setProperty(XMLInputFactory.IS_COALESCING, true);
                XMLEventReader eventReader =
                factory.createXMLEventReader( new FileReader(it.next())  );
                
                while(eventReader.hasNext()){
                    XMLEvent event = eventReader.nextEvent();
                    switch(event.getEventType()){
                        case XMLStreamConstants.START_ELEMENT:
                            StartElement startElement = event.asStartElement();
                            String tagName = startElement.getName().getLocalPart();
                            //Atribuição de valores de flags para a distinção de id
                            if(tagName.equalsIgnoreCase("revision")){
                            	revision = true;
                            }
                            if(tagName.equalsIgnoreCase("contributor")){
                            	contributor = true;
                            	revision = false;
                            }
                            if(tagName.equalsIgnoreCase("page")){
                            	contributor = false;
                            	revision = false;
                            }
                            //Verifica qual o tipo do proximo tipo de texto importante.
                            if (tagName.equalsIgnoreCase("title")) {
                                pageTitle = true;
                            } else if (tagName.equalsIgnoreCase("id") && !contributor && !revision) {
                                idArtigo = true;
                            } else if (tagName.equalsIgnoreCase("id") && revision && !contributor ) {
                                revisionId = true;
                            } else if (tagName.equalsIgnoreCase("timestamp")) {
                                revisionTimestamp = true;
                            } else if (tagName.equalsIgnoreCase("username")) {
                                contriUser = true;
                            } else if (tagName.equalsIgnoreCase("id") && contributor && !revision) {
                                contriId = true;
                            } else if (tagName.equalsIgnoreCase("text")) {
                                revText = true;
                            } else if (tagName.equalsIgnoreCase("ip")) {
                                ip = true;
                            }
                            break;
                            
                        case XMLStreamConstants.CHARACTERS:
                            Characters characters = event.asCharacters();
                            if(pageTitle){
                            	title = characters.getData();
                            	pageTitle = false;
                            }
                            if(idArtigo){
                            	idL = Long.valueOf(characters.getData());
                            	id = idL.longValue();
                            	idArtigo = false;
                            }
                            if(revisionId){
                            	revIdL = Long.valueOf(characters.getData());
                            	revId = revIdL.longValue();
                                revisionId = false;
                            }
                            if(revisionTimestamp){
                            	revTs = characters.getData();
                                revisionTimestamp = false;
                            }
                            if(contriUser){
                            	ctName = characters.getData();
                                contriUser = false;
                            }
                            if(contriId){
                            	ctIdL = Long.valueOf(characters.getData());
                            	ctId = ctIdL.longValue();
                                contriId = false;
                            }
                            if(revText){
                            	byte [] b = characters.getData().getBytes();
                            	revTextSize = b.length;
                            	revTextWords = countWords(characters.getData());
                                revText = false;
                            }
                            
                            
                            break;
                            
                        case  XMLStreamConstants.END_ELEMENT:
                            EndElement endElement = event.asEndElement();
                            //Caso tenha chegado ao fim de uma "page"
                            if(endElement.getName().getLocalPart().equalsIgnoreCase("page")){
                            	
                            	//Criação dos elementos a adicionar.
                            	Article toAdd = new Article(id, revTextWords, revTextSize, title);
                                Revision toAddRev = new Revision(revId, ctId, ctName, revTs);
                                Contributor toAddCt = new Contributor(ctId, ctName);
                                //Verificação de duplicado e inserção de não duplicados.
                                if(this.hashArts.putIfAbsent(idL, toAdd) != null){
                                	//Caso duplicado aumentar variavel de instancia de duplicados.
                                	toAdd.setDups(this.hashArts.get(idL).getDups() + 1);
                                	
                                	//Verificar se o tamanho do texto é maior que o atual
                                	if(this.hashArts.get(idL).getNChar() > revTextSize){
                                		//Caso o texto seja maior que o atual o atual passa a ser o novo.
                                		toAdd.setNchar(this.hashArts.get(idL).getNChar());
                                	}
                                	//Verificar se o numero de palavras é maior que o atual.
                                	if(this.hashArts.get(idL).getNWords() > revTextWords){
                                		//Caso o numero de palavras seja maior do que o atual, atual para a ser o novo
                                		toAdd.setNwords(this.hashArts.get(idL).getNWords());
                                	}
                                	//Substituição do artigo.
                                	this.hashArts.put(idL, toAdd);
                                }
                                //Verificação de duplicado para contribuidores.
                                if(this.hashRevs.putIfAbsent(revIdL, toAddRev) != null){
                                	//Caso seja um revisão presente num snapshot anterior, alterar valor da flag.
                                	repRev = true;
                                }
                                
                                //ignorar contribuidores com apenas um ip.
                                if(!ip){
                                	//Inserçao de novos contribuidores.
                                	if(this.hashConts.putIfAbsent(ctIdL, toAddCt) != null){
                                		//Verificação da contribuição
                                		if(repRev){
                                			//Revisão presente tambem num snapshot anterior.
                                			toAddCt.setContributions(this.hashConts.get(ctIdL).getNCont());
                                			//Atualização da flag
                                			repRev = false;
                                		} //Caso de nova contribuição.
                                		else toAddCt.setContributions(this.hashConts.get(ctIdL).getNCont() + 1);
                                		//Substituiçao do contribuidor antigo.
                                		this.hashConts.put(ctIdL, toAddCt);
                                	}
                                } else ip = false; //Atualização da flag
                            }
                            break;
                    }		    
                }
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            } catch (XMLStreamException e) {
                e.printStackTrace();
            }
    	}
    }

    public long all_articles() {
    	//O original conta como um duplicado, razão pela qual nao se soma ainda ao valor o size do hashmap.
        return hashArts.values().stream().mapToInt(a -> a.getDups()).sum();
    }

    public long unique_articles() {
        return hashArts.size();
    }

    public long all_revisions() {
        return hashRevs.size();
    }

    public ArrayList<Long> top_10_contributors() {
    	//Comparador que ordena contribuidores de ordem decrescente de acordo com o seu numero de contribuiçõs.
    	Comparator<Contributor> cmp = new Comparator<Contributor>(){
    		public int compare(Contributor a, Contributor b){
    			return Integer.compare(b.getNCont(), a.getNCont());
    		}
    	};
    	/*
    	 * 		Depois de criar a stream, ordena de acordo com o comparador, corta a stream para ter apenas 10 elementos,
    	 * substitui os elementos(Contribuidores) pelo seu numero de contribuiçõs, adiciona todos os elementos da stream 
    	 * para um novo ArrayList.
    	 */
    	return this.hashConts.values().stream().sorted(cmp).limit(10).mapToLong(c -> c.getColID()).collect(ArrayList :: new, ArrayList :: add, ArrayList :: addAll);
    }

    public String contributor_name(long contributor_id) {
        return hashConts.get(contributor_id).getNome();
    }

    public ArrayList<Long> top_20_largest_articles() {
    	/*
    	 * Comparador que ordena Artigos de acordo com o tamanho do seu texto.
    	 */
    	Comparator<Article> cmp = new Comparator<Article>(){
    		public int compare(Article a, Article b){
    			return (int) (b.getNChar() - a.getNChar());
    		}
    	};
    	/*
    	 * 		Depois de criar a stream, ordena de acordo com o comparador, corta a stream para ter apenas 20 elementos,
    	 * substitui os elementos(Artigos) pelo tamanho do texto do mesmo, adiciona todos os elementos da stream a um novo 
    	 * ArrayList.
    	 */
    	return this.hashArts.values().stream().sorted(cmp).limit(20).mapToLong(c -> c.getID()).collect(ArrayList :: new, ArrayList :: add, ArrayList :: addAll);
    }

    public String article_title(long article_id) {

        return hashArts.get(article_id).getTitulo();
    }

    public ArrayList<Long> top_N_articles_with_more_words(int n) {
    	//Comparador de Artigos que ordena de ordem decrescente de acordo com o numero de palavras
    	Comparator<Article> cmp = new Comparator<Article>(){
    		public int compare(Article a, Article b){
    			return (int) (b.getNWords() - a.getNWords());
    		}
    	};
    	/*
    	 * 		Depois de criar a stream, ordena de acordo com o comparador, corta a stream para ter apenas 20 elementos,
    	 * substitui os elementos(Artigos) pelo numero de palavras do texto do mesmo, adiciona todos os elementos da stream 
    	 * a um novo ArrayList.
    	 */
    	return this.hashArts.values().stream().sorted(cmp).limit(n).mapToLong(c -> c.getID()).collect(ArrayList :: new, ArrayList :: add, ArrayList :: addAll);
    }

    public ArrayList<String> titles_with_prefix(String prefix) {
    	/*
    	 * 		Depois de criar a stream, substitui os Artigos da stream pelo seu titulo, elimina os elementos da stream 
    	 * que não têm o prefixo especificado, ordena alfabeticamente os elementos e adiciona todos os elementos da stream 
    	 * a um novo ArrayList.
    	 */
    	return this.hashArts.values().stream().map(a -> a.getTitulo()).filter(s -> s.startsWith(prefix))
    			.sorted().collect(ArrayList :: new, ArrayList :: add, ArrayList :: addAll);

    }

    public String article_timestamp(long article_id, long revision_id) {
        return hashRevs.get(revision_id).getTimestamp();
    }

    public void clean() {
    	//Remove todos os "Key to Value" mappings dos maps.
    	hashArts.clear();
    	hashRevs.clear();
    	hashConts.clear();
    }
}
