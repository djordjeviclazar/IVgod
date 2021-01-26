comm program
begin
 (*ovo je komentar*)
 var a:integer b:char;
 a:=356;
 b:='c'
end ~comm

model

    ABCA : int;; 
    
    W : double;; SAD : string;;
    SERVERA: string;
    
    comm Identifikatori imaju samo velika slova i cifre ~comm
    
    ABCA := -2.22321; W := 2; SAD := "fajdnfls?*!";

    while (ABCA less W) :
    {
        ABCA := W + 1;
        ABCA := ABCA + ABCA
    }
    
    deployment
    
        task
            taskId SIMPLE,
            SAD,
            executedOn SERVERA
        ~task
    
        server
    
            serverId SERVERA,
            ABCA
    
        ~server
    
    ~deployment

~model
