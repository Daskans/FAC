(* Consigne générale: structurer proprement vos scripts de preuve;
   chaque fois qu'une tactique produit plus d'un but, utiliser des
   puces pour séparer les preuves des deux buts.

   Vous pouvez aussi essayer, autant que possible, d'enchaîner les
   tactiques au moyen de points-virgules.
*)

(* Tous les "Admitted" doivent être remplacés par vos scripts de preuves. *)

(* Quelques lemmes à prouver *)
Section Complements_Negation.
Variables P Q R S: Prop.

Lemma contraposee: (P->Q) -> (~Q->~P).
Proof.
intros Hpq HNq Hp.
apply HNq.
apply Hpq;assumption.

Qed.

Lemma autre_contraposee: (P->~Q) -> (Q->~P).
Proof.
intros HpNq Hq Hp.
apply HpNq;assumption.
Qed.

Lemma DS1: ((P->Q)->R)->((~P->~Q)->~R)->(P->Q->S).
Proof.
intros Hpqr HNpNqNr Hp Hq.
exfalso.
apply HNpNqNr.
- intro HNp.
  exfalso.
  apply HNp;assumption.
- apply Hpqr.
  intro Hp2;assumption.
Qed.

Lemma DS2: (P->Q)->~(R->Q)->(~R->S) -> (R->P->S).
Proof.
intros Hpq NHrq HNrs Hr Hp.
apply HNrs.
exfalso.
apply NHrq.
intro Hr2.
apply Hpq;assumption.

Qed.

(* Ne pas foncer sans réfléchir *)
Lemma piege: (P->~Q)->(~Q->R)->(R->~S)->(~S->~P) -> ~P.
Proof.
intros H1 H2 H3 H4.
intro Hp.
apply H4.
- apply H3.
  apply H2.
  apply H1;assumption.
- assumption.
(* à compléter *)
Qed.

End Complements_Negation.

Section Double_Negation.
(* Autour de la double négation *)
Variables P Q: Prop.
(* De P, on peut déduire non-non-P *)
Lemma dn_i: P-> ~~P.
Proof.
intros Hp HNp.
apply HNp;assumption.
Qed.

(* On a prouvé dans absurd' (fichier negation.v), que, de "non-P implique P",
   on peut déduire, peut-être pas P, mais au moins non-non-P *)

(* Si on suppose, ce qui est plus fort, qu'on peut déduire P
   de "non-P implique P", alors on peut justifier l'élimination de
   la double négation [pour P] *)
Lemma trop_de_negations: ((~P->P)->P) -> (~~P -> P).
Proof.
intros HNppp HNNp.
apply HNppp.
intro HNp.
exfalso.
apply HNNp;assumption.
Qed.

End Double_Negation.


Section Preuves_de_sequents.
Variables P Q R S: Prop.
(* Les exercices restants consistent à formuler soi-même les lemmes:
   chaque séquent à prouver va constituer une sous-section, avec ses
   hypothèses *)

(* Et bien sûr, faire la preuve ensuite! *)


(* Exemple *)
Section Exemple.
(* Séquent à prouver: P->Q, P->~Q |- P->R *)
Hypothesis H: P->Q.
Hypothesis H1: P->~Q.
Lemma exemple: P->R.
Proof.
intro p. exfalso.
apply H1.
- assumption.
- apply H. assumption.
Qed.
End Exemple.

Section Sequent1.
(* Séquent à prouver: 
   (P->Q)->~Q |- (P->Q)->~P
*)
Hypothesis H: (P->Q)->~Q.
Lemma Seq1: (P->Q)->~P.
Proof.
intros Hpq Hp.
apply H.
- assumption.
- apply Hpq;assumption.
Qed.
End Sequent1.

Section Sequent2.
(* Séquent à prouver:
   (P->Q)->R, (P->Q)->~R |- Q->S
*)
Hypothesis H: (P->Q)->R.
Hypothesis H1: (P->Q)->~R.
Lemma Seq2: Q->S.
Proof.
intro Hq.
exfalso.
apply H1.
- intro Hp;assumption.
- apply H.
  intro Hp2;assumption.
Qed.

End Sequent2.

Section Sequent3.
(* Séquent à prouver:
   P->Q, ~P->Q |- ~~Q
*)
Hypothesis H: P->Q.
Hypothesis H1: ~P->Q.
Lemma Seq3: ~~Q.
Proof.
intro HNq.
apply HNq.
apply H1.
intro Hp.
apply HNq.
apply H;assumption.
Qed.

End Sequent3.

End Preuves_de_sequents.