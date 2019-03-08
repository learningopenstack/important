
/* 
 * time: O(n);
 * space: O(n);
 * @param p
 * @param q
 * @return bool
 */
bool isSameTree(TreeNode p, TreeNode q){
    if(p==NULL && q == NULL){
        return true;
    }
    if(p==NULL || q == NULL){
        return false;
    }

    if(p->val != q->val){
        return false;
    }
    return isSameTree(p->r, q->r) && isSameTree(p->l, q->l);
}
