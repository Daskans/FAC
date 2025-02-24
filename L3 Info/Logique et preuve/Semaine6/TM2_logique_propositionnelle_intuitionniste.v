Require Import Setoid.
(*  Logique intuitionniste *)

Section LJ.
Variables P Q R S T : Prop.
(*  Tactiques pour la conjonction 

    Introduction : pour prouver A /\ B : split (il faudra prouver A, puis B)
    Elimination : si H : A /\ B, utiliser: destruct H as [H1 H2].
        On récupère deux hypothèses pour A et B (et on 
        choisit leurs noms, ici H1 et H2)
*)
Lemma and_comm : P /\ Q -> Q /\ P.
Proof.
intro H.
destruct H as [H0 H1].
split; assumption. (* "assumption" résout les deux sous-buts *)
Qed.

(* tactiques pour la disjonction 
   Introduction:
     pour prouver A \/ B a partir de A : left
     pour prouver A \/ B a partir de B : right

   Elimination:
     preuve par cas : si H: A \/ B
                      destruct H as [H1 | H2]
     On aura a faire deux preuves, une pour chaque cas (cas A, cas B)
     Noter la différence de syntaxe: la barre verticale entre les deux noms.
     On peut utiliser deux fois le même nom: les hypothèses seront présentes dans
     deux sous-preuves différentes.
*)

Lemma or_not : P \/ Q -> ~P -> Q.
Proof.
intros H H0.
destruct H as [h1 | h1].
- exfalso.
  apply H0; assumption.
  (* alternative: 
     assert (f:False).    
     {
       apply H0; trivial.
     }
     destruct f. *)
  (* "destruct f" sur f:False résoud n'importe quel but *)
- assumption.
Qed.

(*  equivalence logique (<->, iff):
    unfold iff transforme A <-> B en
                         (A -> B) /\ (B -> A).
    donc split, destruct, etc, marchent

    (iff pour "if and only if", le "si et seulement si" en anglais)
*)

Lemma iff_comm : (P <-> Q) -> (Q <-> P).
Proof.
intro H.
destruct H as [Hpq Hqp].
split.
- assumption.
- assumption.
(* "assumption" résoud les deux sous-buts engendrés par "split"
  donc on peut remplacer les trois dernières lignes par
  split; assumption.
*)
Qed.

(* la regle de remplacement est implantée en Coq *)
(* "rewrite H" fait un remplacement uniforme quand H est une
   équivalence *)
(* "rewrite H" réécrit le but courant avec H *)
(* "rewrite H in H'" fait la réécriture de H dans une autre hypothèse H' *)
(* "rewrite <- H" réécrit dans l'autre sens, le membre droit par le gauche *)
Lemma L1 : (P <-> Q) -> ~(Q <-> ~P).
Proof.  
intro H.
rewrite H.
intro H0.
destruct H0 as [Hqnq Hnqq].
assert (nq:~Q).
{ intro q.
  apply Hqnq; assumption.
}
apply nq. apply Hnqq. assumption. 
Qed.

(* Fin des exemples, début des exercices *)

(* Exercice : remplacer chaque Admitted par un script de preuve,
   terminé par Qed. *)
(*  Exercices de la feuille 4 *)

Lemma and_false : P /\ False -> False.
Proof.
(*
intro HpON.
apply HpON. 
*)
intro HpAN.
destruct HpAN as [Hp HN];assumption.
Qed.

Lemma and_assoc : (P /\ Q) /\ R <-> P /\ (Q /\ R).
Proof.
split.
- intro HpAqAr.
  destruct HpAqAr as [HpAq Hr].
  destruct HpAq as [Hp Hq].
  split.
  + assumption.
  + split;assumption.
- intro HpAqAr.
  destruct HpAqAr as [Hp HqAr].
  destruct HqAr as [Hq Hr].
  split.
  + split;assumption.
  + assumption.
  
Qed.

(* Ex. 2 *)
Lemma or_to_imp: ~ P \/ Q -> P -> Q.
Proof.
intros HNpOq Hp.
destruct HNpOq as [HNp | Hq].
- exfalso.
  apply HNp;assumption.
- assumption.
Qed.   

Lemma not_or_and_not: ~(P\/Q) -> ~P /\ ~Q.
Proof.
intro NHpOq.
split.
- intro Hp.
  apply NHpOq.
  left;assumption.
- intro Hq.
  apply NHpOq;right;assumption. 
Qed.

(* Exercice 4 *)
Lemma absorption_or: P \/ False <-> P.
Proof.
split.
- intro HpON.
  destruct HpON as [Hp | HN].
  + assumption.
  + exfalso;assumption.
- intro Hp.
  left;assumption.

Qed.

Lemma and_or_dist : P /\ (Q \/ R) <-> P /\ Q \/ P /\ R.
Proof.
split.
- intro HpAqOr.
  destruct HpAqOr as [Hp HqOr].
  destruct HqOr as [Hq | Hr].
  + left;split;assumption.
  + right;split;assumption. 
- intro HpAqOpAr.
  destruct HpAqOpAr as [HpAq | HpAr].
  destruct HpAq as [Hp Hq].
  + split.
    * assumption.
    * left;assumption.
  + destruct HpAr as [Hp Hr].
    split.
    * assumption.
    * right;assumption.
Qed.

Lemma or_and_dist : P \/ (Q /\ R) <-> (P \/ Q) /\ (P \/ R).
Proof.
split.
- intro HpOrAr.
  destruct HpOrAr as [Hp | HqAr].
  + split;left;assumption.
  + split;destruct HqAr as [Hq Hr];right;assumption.
- intro HpOqApOr.
  destruct HpOqApOr as [HpOq HpOr].
  destruct HpOq as [Hp | Hq].
  + left;assumption.
  + destruct HpOr as [Hp | Hr].
    * left.
      assumption.
    * right.
      split;assumption.
Qed.

Lemma and_not_not_impl: P /\ ~ Q -> ~(P -> Q).
Proof.
intro HpANq.
destruct HpANq as [Hp HNq].
intro Hpq.
apply HNq.
apply Hpq.
assumption.
Qed.

Lemma de_morgan1 : ~ (P \/ Q) <-> ~P /\ ~Q.
Proof.
split.
- intro NHpOq.
  split.
  + intro Hp.
    apply NHpOq.
    left;assumption.
  + intro Hq.
    apply NHpOq.
    right;assumption.
- intro NHpONq.
  intro HpOq.
  destruct NHpONq as [HNp HNq].
  destruct HpOq as [Hp | Hq].
  apply HNp;assumption.
  apply HNq;assumption.
Qed.

Lemma reductio_ad_absurdum: (P -> ~P) -> ~P.
Proof.
intros HpNp Hp.
apply HpNp;assumption.
Qed.

Lemma np_p_nnp: (~P -> P) -> ~~P.
Proof.
intros HNpp HNp.
apply HNp.
apply HNpp;assumption.
Qed.

(* Exercice: reprendre toutes les preuves précédentes, 
   en simplifiant et clarifiant les scripts si ce n'est
   pas déjà fait:
   - structurer les sous-preuves avec +/-/*
   - inversement, quand c'est possible, factoriser avec 
     l'enchainement de tactiques (par ";")

   Le but est de faire que le script soit plus facile à lire
   par un humain, pas pour la machine.
*)
  
End LJ.