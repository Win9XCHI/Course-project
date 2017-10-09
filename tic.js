/*$(document).ready(function(){
$('.tab2').hide();
$('.ticket').click(function(){
    $(this).next().toggle()});
});

$(document).ready(function(){
$('.box_text').hide();
$('.computing').click(function(){
    $(this).next().toggle()});
});*/

$('.box_text').toggle();
/*$('#computing').click(function(){
    
});*/

$('.tab2').toggle();
$('.tickets').click(function(){
    $('.tab2').toggle();
});

$('.tab3').toggle();
$('.tickets').click(function(){
    $('.tab3').toggle();
});

$('#box_text').toggle();
$('.computing').click(function(){
    $('#box_text').toggle();
});

$('.spoiler-title').click(function(){
    $('#map').toggle();
});

$('.blue').click(function() {
    $(this).toggleClass('checked');
});
