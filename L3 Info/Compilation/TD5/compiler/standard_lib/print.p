null printInt(int x) ::=
{
    if x = 0 then {
        print "0";
        return;
    }
    if x < 0 then {
        x := -x;
        print "-";
    }
    int t[64];
    int p;
    p := 0;
    while(x > 0)
    {
        t[p] := x % 10;
        x := x/10;
        p := p+1;
    }
    p := p-1;
    while(p >= 0)
    {
        if t[p] = 0 then print "0";
        if t[p] = 1 then print "1";
        if t[p] = 2 then print "2";
        if t[p] = 3 then print "3";
        if t[p] = 4 then print "4";
        if t[p] = 5 then print "5";
        if t[p] = 6 then print "6";
        if t[p] = 7 then print "7";
        if t[p] = 8 then print "8";
        if t[p] = 9 then print "9";
        p := p-1;
    }
    return;
}

null printBool(bool x) ::=
    if x then print "true"; else print "false";

null printFloat(float x) ::=
{
    if x < 0. then {
        print "-";
        x := - x;
    }
    int exponent;
    exponent := 0;
    while x >= 10. {
        x := x/10.;
        exponent := exponent+1;
    }
    while x < 1. {
        x := x*10.;
        exponent := exponent-1;
    }
    int point_pos;
    bool exp_mode;
    if (-5 <= exponent && exponent <= 10) then {
        point_pos := exponent;
        exp_mode := false;
        }
    else {
        point_pos := 0;
        exp_mode := true;
    }
    int num;
    float limit;
    limit := 0.0000000001;
    num := 0;
    if point_pos < 0 then print "0.";
    while (point_pos < -1) {
        print "0";
        num := num+1;
        point_pos := point_pos + 1;
    }
    while (num < 12 && (x >= limit || point_pos >= 0)){
        if (x < 1.) then print "0";
        else if (x < 2.) then print "1";
        else if (x < 3.) then print "2";
        else if (x < 4.) then print "3";
        else if (x < 5.) then print "4";
        else if (x < 6.) then print "5";
        else if (x < 7.) then print "6";
        else if (x < 8.) then print "7";
        else if (x < 9.) then print "8";
        else print "9";
        num := num +1;
        x := (x*10.) % 10.;
        if point_pos = 0 then print ".";
        limit := limit * 10.;
        point_pos := point_pos - 1;
    }
    if(exp_mode) then{
        print "e";
        printInt(exponent);
    }
    return;
}