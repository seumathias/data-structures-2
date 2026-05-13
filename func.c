void priorizar(List lst, int id){
    // ... (seu código inicial)
    if(target->id == id){
        target->before->next = target->next;
        
        if(target->next)
            target->next->before = target->before;
        else
            lst->tail = target->before;
        
        target->next = lst->head;
        lst->head->before = target;
        
        lst->head = target;
        target->before = NULL; // <--- ADICIONE ESTA LINHA!
        return;
    }
    // ...
}
