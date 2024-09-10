using Emporium.Models;
using Emporium.Data;


namespace Emporium.Repository{

    public class LeilaoRepository : ILeilaoRepository{

        private readonly FeiraContext _feiracontext;

        public LeilaoRepository(FeiraContext feiraContext){
            _feiracontext = feiraContext;
        }        
        public LeiloesModel BuscaLeilao(string leilao){
            //return _context.Users.FirstOrDefault(x => x.Login.ToUpper() == login.ToUpper());
            return null;
        }

        public LeiloesModel Adicionar(LeiloesModel leilao){
            _feiracontext.Leiloes.Add(leilao);
            _feiracontext.SaveChanges();
            return leilao;
        }

        public List<LeiloesModel> BuscaTodos(){
            return _feiracontext.Leiloes.ToList();
        }
    }
}