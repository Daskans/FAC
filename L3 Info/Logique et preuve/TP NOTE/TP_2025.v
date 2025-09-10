Require Import Setoid Classical.

Ltac forall_e H t Hname:= (generalize (H t); intro Hname).

Section K.

Variable Personnage: Type.
Variables Breton Romain Hun : Personnage -> Prop.
Variables Chef : Personnage -> Personnage -> Prop. (*Chef x y : x est le chef de y*)
Variables Perceval Arthur Attila : Personnage.

Hypothesis un_Hun: forall x y, Hun x -> Hun y -> x = y.
Hypothesis BPerceval : Breton Perceval.
Hypothesis HAttila : Hun Attila.
Hypothesis CAttila : forall x, Hun x -> Chef Attila x.

Hypothesis Arturus_rex : forall x, Breton x <-> Chef Arthur x.
(* L'hypothèse Arturus_rex est équivalente à la conjonction des deux
   suivantes A_rex_1 et A_rex_2, qui peuvent être un peu plus faciles 
   à utiliser. C'est au choix! *)
Hypothesis A_rex_1: forall x, Breton x -> Chef Arthur x.
Hypothesis A_rex_2: forall x, Chef Arthur x -> Breton x.
Hypothesis le_monde_est_petit : forall x, Breton x \/ Romain x \/ Hun x.

Hypothesis HRB  : forall x,  ~ (Romain x /\ Breton x).
Hypothesis HRH  : forall x,  ~ (Romain x /\ Hun x).
Hypothesis HBH  : forall x,  ~ (Breton x /\ Hun x).

(* Exemple *)
Lemma Q0: ~ Romain Attila.
Proof.
intro HrAtt.
specialize HRH with (x:=Attila) as HrhAtt.
apply HrhAtt.
split.
- assumption.
- assumption.
Restart.
intro HrAtt.
forall_e HRH Attila HrhAtt.
apply HrhAtt.
split; assumption.
Qed.

Lemma Q1 : exists x : Personnage, Chef x Perceval. 
Proof.
exists Perceval.

Admitted.

Lemma Q2 : forall x : Personnage, Romain x -> ~Chef Arthur x.
Proof.
intros HNArthur Hr.
intro HcArt.
specialize HRB with (x:=Arthur) as HrbArt.
apply HrbArt.
split.
-  
Admitted.

Lemma Q3 : exists x : Personnage, ~Chef Arthur x.
Proof.
exists Attila.
intro HcArtAtt.
specialize HBH with (x:=Attila) as HbhAtt.
apply HbhAtt.
split.
-  
Admitted.

Lemma Q4 : forall x : Personnage, x<>Attila -> ~Chef Arthur x -> Romain x.  
Proof.
unfold not.
intros Hr HNatt HNart.



Admitted.

Lemma Q5 : forall x y : Personnage, Hun x /\ Hun y-> Chef x y. 
Proof.
intros HPx HPy HPxAPy.
specialize un_Hun with (x:=HPx) as H.
specialize H with (y:=Attila) as H.
destruct HPxAPy as [H0 H1].
specialize CAttila with (x:=HPx) as H2.

Admitted.

End K.

(* La question 6 est OPTIONNELLE, il s'agit de justifier (avec d'autres noms)
   l'affirmation sur les hypothèses Arturus_rex, A_rex_1 et A_rex_2 *)
Section Complement.

Variable P: Type.
Variable B : P -> Prop.
Variable a: P.
Variable C: P -> P -> Prop.

Lemma Q6: 
  (forall x : P, B x <-> C a x) <-> 
  (forall y : P, B y -> C a y) /\ (forall z : P, C a z -> B z).
Proof.
Admitted.

End Complement.