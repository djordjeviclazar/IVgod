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
    SERVERA: string;; SIMPLE: int;
    
    comm Identifikatori imaju samo velika slova i cifre ~comm
    
    ABCA := -2.22321; W := 2; SAD := "fajdnfls?*!";

    while (ABCA less W) :
    {
        ABCA := ABCA + 1;
        ABCA := ABCA + ABCA
    }
    default
    {
        SIMPLE := 1
    }
    deployment
    
        task
            taskId SIMPLE,
            ABCA,
            executedOn SERVERA
        ~task
    
        server
    
            serverId SERVERA,
            ABCA
    
        ~server
    
    ~deployment

~model
