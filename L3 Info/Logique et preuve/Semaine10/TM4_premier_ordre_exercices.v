(* Logique du premier ordre, version 2025 *)
Require Import Classical.
(* Dans tout le fichier, vous avez accès aux tactiques
   spécifiques à la logique classique, notamment
   classical_left et classical_right, ainsi que les deux
   tactiques "maison" absurdK et add_exm.

   Les exercices où elles sont nécessaires sont marqués
   d'un commentaire (LK); essayez de faire les autres
   exercices en restant dans un cadre intuitionniste. *)

(** Tactiques :
  pour forall :  
    introduction : 
            intro, intros.
    elimination :
            apply, eapply, specialize.
            (H x ...)

  pour exists : 
     introduction: exists (fournir le terme)
     elimintation: destruct.

  pour = reflexivity (introduction),
         rewrite H   [in HØ] (elimination)
         rewrite <- H [in H0]
                  
 *)

(* tactique maison pour eliminer un forall *)
(* il faut fournir le terme temoin *)

Ltac forall_e H t Hname:= (generalize (H t); intro Hname).

(* Compléments sur "specialize": permet de spécialiser
  une hypothèse H (quantifiée universellemnt) en
  fournissant une valeur (terme) pour une ou plusieurs
  variables. Syntaxe:
  specialize H with (x:=t) 
     va remplacer H par "H appliquée à t", la variable x
     est remplacée par t
  specialize H with (x:=t) as H0
     similaire mais laisse H inchangée, on obtient une
     nouvelle hypothèse H0
     
  Au final c'est plus souple que forall_e, en particulier
  quand H a plusieurs variables quantifiées
  universellement. 
  *)

(* Deux autres tactiques maison, réservées au cadre
   classique *)
(* "add_exm P H" fait apparaître une hypothese P\/~P *)
Ltac add_exm  P hname :=
assert(hname : P \/ ~P); [classical_right; assumption|].

(* absurdK: applique le raisonnement par l'absurde classique 
  Transforme un but  "Gamma |- P " en 
                     "Gamma, ~P |- False" *)
Ltac absurdK h :=
  match goal with |- ?X =>
      add_exm X h; destruct h as [ hname | h]; [assumption | exfalso]
  end. 

Section Egalite. (* sur l'egalite *) 
Variable A : Type.
Variable f : A -> A.

(* x <> y est une abréviation de ~ (x = y) *)
(* "unfold not" va faire apparaître l'implication vers False *)
  
(* L'égalité est transitive *)
Lemma Egal3 : forall x y z: A , x = y -> x <> z -> z <> y.
Proof.
intros.

Qed.

(* Contraposée de "si x=y, alors f(x)=f(y)" *)
Lemma L4 : forall x y:A, f x <> f y -> x <> y.
Proof.
Admitted.

End Egalite.

(* Quelques preuves de logique du premier ordre *)

(* Supprimer les "Admitted" (on admet la preuve complète) et 
  les "admit" (on admet le but courant) dans toutes les preuves
  qui suivent, les compléter et le terminer par "Qed." *)

Section QuelquesPreuves.
Variable A B: Type.
Variables P Q : A -> Prop.
Variable R : A -> B -> Prop.
Variable X : Prop.

Lemma Question1 : (forall x:A, P x /\ Q x) <->
                  (forall x:A, P x) /\ (forall x:A, Q x).
Proof.
Admitted.

(* Noter qu'ici, on montre seulement une implication; voir
   en fin de fichier la Question2' pour une équivalence
   (en logique classique) *)
Lemma Question2 : (forall x, P x) \/ (forall x, Q x) ->
                  forall x, P x \/ Q x.
Proof.
Admitted.

(* Là aussi, on montre une implication; voir Question3'
   pour une version avec équivalence *)
Lemma Question3 : (exists x:A, P x /\ Q x) ->
                  (exists x:A, P x) /\  (exists x:A, Q x).
Proof.
Admitted.

Lemma Question3' : (exists x y, P x /\ Q y) <->
                  (exists x:A, P x) /\  (exists x:A, Q x).
Proof.
Admitted.

Lemma Question4 : (exists x:A, P x \/ Q x) <->
                  (exists x:A, P x) \/   (exists x:A, Q x).
Proof.  
Admitted.

Section Question5.
Hypothesis H : forall x, P x -> Q x.
Hypothesis H0 : exists x, P x.

Lemma L5 : exists x, Q x.
Proof.
Admitted.

End Question5.
 
(* Attention au parenthésage: il est implicite *)
Lemma Question6 : forall x,  (P x -> exists y,  P y).
Proof.
Admitted.


Lemma Question7 : ~(exists x, P x) <-> forall x, ~ P x.
Proof.                                      
Admitted.
(* Voir Classical_Question1 pour la version où la négation
   porte sur le forall *)

(* Ici, X joue le rôle de n'importe quelle proposition où x n'est
   pas libre *)
(* Noter le changement de quantificateur! *)
Lemma Question8 : ((exists x, P x) -> X) <->
                   forall x, P x -> X.
Proof.
Admitted.

(* Pas de version avec équivalence ici *)
Lemma Question9 :  (exists x:A, forall y:B, R x y)
                    -> (forall y:B, exists x:A, R x y).
Proof. 
Admitted.

Lemma eq_trans : forall x y z:A, x = y -> y = z -> x = z.
Proof.
Admitted.

End QuelquesPreuves.

Section TypeVide.
(* Dans cette section, on envisage la possibilité que le type A
  soit vide *)
Variable A: Type.
Variable P: A->Prop.

Definition A_est_vide := forall x:A, x <> x.
(* Attention, on n'affirme pas que A est vide; on définit une
  formule qui dit que A est vide (mais on ne la prouve pas)  *)

(* "Si A est vide, alors les éléments de A ont toutes les
  propriétés" *)
Lemma TV1 : A_est_vide -> forall x:A, P x.
Proof.
unfold A_est_vide. (* A compléter *)
Admitted.

Lemma TV2 : (forall x y:A, x <> y) -> A_est_vide.
Proof.
Admitted.

End TypeVide.

Section classic.
Variable A: Type.
Variables P Q: A->Prop.

(* (LK); pas facile *)
Lemma Classical_Question1 : ~ (forall x, P x) <-> exists x, ~ P x.
Proof.   
split; intro H.
- absurdK H0.
Admitted. (* finir la preuve; l'autre sens est intuitionniste *)

(* Dans le même esprit; (LK) *)
Lemma Classical_Question2: 
  ~(forall x, P x /\ Q x) <-> exists x, ~ P x \/ ~ Q x.
Proof.
Admitted.

(* (LK); utiliser Classical_Question 1 *)
Lemma Question2' : (forall x, P x) \/ (forall x, Q x) <->
                  forall x y, P x \/ Q y.
Proof.
split; intro H.
- (* (LJ) *)
  admit.
- (* (LK) *)
Admitted.


(* On complète la section "TypeVide", mais en classique *)
(* Pour des raisons techniques, le type s'appelle B *)

Section TypeVideClassique.
Variable B: Type.
Variable PP: B->Prop.

Definition B_est_vide := forall x:B, x <> x.

Hypothesis H : ~ B_est_vide.
Hypothesis H0 : forall x:B, PP x.

(* (LK) *)
Lemma forall_to_exists : exists x:B, PP x. (* difficile *)
(* Toute la difficulté est d'obtenir un x: B; pour cela,
   il faut utiliser l'hypothèse H *)
Proof.
unfold B_est_vide in H.
assert (exists x:B, x = x).
{  absurdK H1.
  admit.
}
Admitted. (* Compléter la preuve, y compris le "admit" *)

End TypeVideClassique.
    
Section DrinkersProblem. (* Problème du buveur *)

(* On va prouver le théorème CLASSIQUE suivant: dans un bar qui
  contient au moins une personne (le patron), il existe une 
  personne qui, si elle boît, tout le monde boit *)

(* Attention au piège: ce n'est pas forcément le patron *)

Variable people : Type.
Variable patron : people.

Variable boit : people -> Prop.
Theorem buveurs : (* (LK) *)
  exists p:people, (boit p -> forall q, boit q).
Proof.
add_exm (forall q, boit q) H.
Admitted. (* Comme précédemment: compléter la preuve *)

End DrinkersProblem.
End classic.


 
