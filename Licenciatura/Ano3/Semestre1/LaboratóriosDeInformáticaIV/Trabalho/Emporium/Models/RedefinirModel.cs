using System.ComponentModel.DataAnnotations;

namespace Emporium.Models{
    public class RedefinirModel{
        [Required(ErrorMessage = "Digite o login")]
        public string Login {get; set;}

        [Required(ErrorMessage = "Digite o email")]

        public string Email {get; set;}

    }
}