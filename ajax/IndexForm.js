$('#computing').click (function () {
	var St_1 = $('#St_1').val ();
	var St_2 = $('#St_2').val ();
	var dat = $('#dat').val ();
    var v1 = $('#v1').val ();
    var v2 = $('#v2').val ();
    var v3 = $('#v3').val ();
    var v4 = $('#v4').val ();
    var v5 = $('#v5').val ();
    var t1 = $('#t1').val ();
    var t2 = $('#t2').val ();
    var t3 = $('#t3').val ();
    var t4 = $('#t4').val ();
    var t5 = $('#t5').val ();
    var t6 = $('#t6').val ();
    var trans = $('#trans').val ();
    var sort = $('#sort').val ();
    
    alert(St_1);
    
    var flag = true;
    var err = "";
    var err1 = "";
    var err2 = "";
    var err3 = "";
    var now = new Date;
    var Entr = new Date(dat);
    
    for (var i = 0; i < St_1.length-1; i++) {
        if (Check(St_1.charAt(i))) {
            flag = false;
            err1 = "Неправильна перша станція. ";
        }
    }
    if (err1 != "") {
        err = err1;
        $('#St_1').css ("border-color", "#f7b4b4");
    } 
    
    for (var i = 0; i < St_2.length-1; i++) {
        if (Check(St_2.charAt(i))) {
            flag = false;
            err2 = "Неправильна друга станція. ";
        }
    }
    if (err2 != "") {
        err = err + err2;
        $('#St_2').css ("border-color", "#f7b4b4");
    }
    
    if (Entr.getFullYear() < now.getFullYear() || Entr.getFullYear() > (now.getFullYear() + 1)) {
        if (now.getMonth() > 9 && Entr.getMonth() > 2) {
            flag = false;
            err3 = "На таку дату розкладу немає. ";
        }
    }
    if (err3 != "") {
        err = err + err3;
        $('#dat').css ("border-color", "#f7b4b4");
    }
    
    if (St_1 == St_2) {
        flag = false;
        err = err + "Станції однакові. "
    }
    
    if (!flag) {
        alert(err);
    }
    else {
        $.ajax({
            url:    	'C:\MAMP\htdocs\php\CheckWay.php',
            type:		'POST',
            cache: 		false,
            data:   	{'St_1':St_1, 'St_2':St_2, 'dat':dat, 'v1':v1, 'v2':v2, 'v3':v3, 'v4':v4, 'v5':v5, 't1':t1, 't2':t2, 't3':t3, 't4':t4, 't5':t5, 't6':t6, 'trans':trans, 'sort':sort},
            dataType:	'html',
            beforeSend: function () {
                $('#computing').attr ("disabled", "disabled");
            },
            error: function(data) {
                if (data == true) {
                    $('.box_text').toggle();
                    $('#St_1').val ("");
                    $('#St_2').val ("");
                    $('#dat').val ("");
                    $('#v1').val ("");
                    ('#v2').val ("");
                    ('#v3').val ("");
                    ('#v4').val ("");
                    ('#v5').val ("");
                    ('#t1').val ("");
                    ('#t2').val ("");
                    ('#t3').val ("");
                    ('#t4').val ("");
                    ('#t5').val ("");
                    ('#t6').val ("");
                    ('#trans').val ("");
                    ('#sort').val ("");
                    //$('#send').text ("Сообщение отправлено");
                    //$('#email').css ("border-color", "#60fc8c");
                    //$('#name').css ("border-color", "#60fc8c");
                    //$('#message').css ("border-color", "#60fc8c");
                } else {
                    if (data == false)				
                        alert ("The error is not related to operation resource");
                    else {					
                        switch (data) {
                        case "C1 (Not open file)":
                            alert ("Error C1. Sorry for any problems, please contact support.");
                            break;
                        case "C11 (Not write file)":
                            alert ("Error C11. Sorry for any problems, please contact support.");
                            break;
                        default:
                            alert ("Error AJAX. Sorry for any problems, please contact support.");
                        }
                    }
                }
                $('#computing').removeAttr ("disabled");				
            }
        });
    }
});

function Check(var str) {
    if (str == '!') {
        return true;
    }
    if (str == '@') {
        return true;
    }
    if (str == '#') {
        return true;
    }
    if (str == '') {
        return true;
    }
    if (str == '$') {
        return true;
    }
    if (str == '%') {
        return true;
    }
    if (str == '^') {
        return true;
    }
    if (str == '&') {
        return true;
    }
    if (str == '*') {
        return true;
    }
    if (str == '(') {
        return true;
    }
    if (str == ')') {
        return true;
    }
    if (str == '{') {
        return true;
    }
    if (str == '}') {
        return true;
    }
    if (str == '[') {
        return true;
    }
    if (str == ']') {
        return true;
    }
    if (str == ';') {
        return true;
    }
    if (str == '\'') {
        return true;
    }
    if (str == ':') {
        return true;
    }
    if (str == '|') {
        return true;
    }
    if (str == '<') {
        return true;
    }
    if (str == '"') {
        return true;
    }
    if (str == '>') {
        return true;
    }
    if (str == '.') {
        return true;
    }
    if (str == ',') {
        return true;
    }
    if (str == '/') {
        return true;
    }
    if (str == '?') {
        return true;
    }
    if (str == '=') {
        return true;
    }
    if (str == '+') {
        return true;
    }
    if (str == '`') {
        return true;
    }
    if (str == '~') {
        return true;
    }
    if (str == '№') {
        return true;
    }   
    if (/[a-zA-Z]/.test(str)) {
        return true;
    }
    return false;
}