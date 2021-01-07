comm program
begin
 (*ovo je komentar*)
 var a:integer b:char;
 a:=356;
 b:='c'
end ~comm

model

    ABCA : int;
     comm W : double; SAD : string; ~comm
    comm Identifikatori imaju samo velika slova i cifre ~comm
    ABCA := -2.22321; W := 2; SAD := "fajdnfls?*!";

    while (ABCA less W) :
    {
        ABCA := ABCA + 1;
        ABCA := ABCA + W
    }
    
    deployment
    
        task
            taskId SIMPLE,
            ABCA,
            executedOn SERVERA
        ~task
    
        server
    
            serverId SERVERA,
            25.7
    
        ~server
    
    

~model
