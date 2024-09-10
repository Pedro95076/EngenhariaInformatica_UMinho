// Please see documentation at https://docs.microsoft.com/aspnet/core/client-side/bundling-and-minification
// for details on configuring this project to bundle and minify static web assets.

// Write your JavaScript code.

$(document).ready(function (){
    $('#table-ofertas').DataTable();
});

$(document).ready(function (){
    $('#table-leiloes').DataTable();
});

$(document).ready(function (){
    $('#table-produtos').DataTable();
});

$(document).ready(function (){
    $('#table-historico').DataTable();
});

$(document).ready(function (){
    $('#table-carrinho').DataTable();
});

$(document).ready(function (){
    $('#table-feiras').DataTable();
});

$('.close-alert').click(function(){
    $(".alert").hide('hide');
});
