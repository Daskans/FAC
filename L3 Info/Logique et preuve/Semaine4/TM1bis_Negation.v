Section Negation.
Variables P Q R S T: Prop.

(* Tactiques nouvelles: *)
(* unfold not: expansion de la négation dans le but *)
(* unfold not in X: expansion de la négation dans l'hypothèse X *)
(* exfalso: transforme le but courant en False; c'est 
   l'équivalent de la règle d'élimination de la contradiction *)

(* Executez cette preuve en essayant de comprendre le sens de chacune des nouvelles tactiques utilisées. *)
Lemma absurde_exemple: P -> ~P -> S.
Proof.
intros p np.
unfold not in np.
exfalso.
apply np.
assumption.
Qed.
  
Lemma triple_neg_e : ~~~P -> ~P.
Proof.
intro H. 
intro H0.
apply H.
intro H1.
apply H1; assumption.
Qed.

(* Début des exercices *)

(* QUESTION: Remplacer les Admitted par des scripts de preuve *)
Lemma absurde: (P -> Q) -> (P -> ~Q) -> (P -> S).
Proof.
intros Hpq HpNq Hp.
unfold not in HpNq.
exfalso.
apply HpNq.
- assumption.
- apply Hpq.
  assumption.
Qed.

Lemma triple_neg_i: ~P -> ~~~P.
Proof.
intro HNp.
unfold not.
unfold not in HNp.
intro HNNp.
apply HNNp.
assumption.
Qed.
  
Lemma absurde' : (~P -> P) -> ~~P.
Proof.
intro HNpp.
unfold not.
intro HNp.
apply HNp.
unfold not in HNpp.
apply HNpp.
assumption.
Qed.

Definition Peirce  := ((P -> Q) -> P) -> P.

(* On va prouver non-non-Peirce *)
Lemma Peirce_2 : ~~ Peirce.
Proof.
(* Strategie: sous hypothese ~Peirce [par intro], montrer ~P,
   puis s'en servir pour montrer Peirce; alors on aura une
   contradiction entre Peirce et ~Peirce *)
(* Indication: à un moment vous ferez peut-être un
   "unfold Peirce" (pour remplacer Peirce par sa définition)
   ou "unfold Peirce in X" (pour le remplacer dans une
   hypothèse) *)
intro nonPeirce.
unfold Peirce in nonPeirce.
unfold not in nonPeirce.
assert (HNp: ~P). {
exfalso.
apply nonPeirce.
intro Hpqp.
apply Hpqp.
intro Hp.
exfalso.
apply nonPeirce.
intro Hpqp2.
assumption.
}
unfold not in HNp.
apply nonPeirce.
intro Hpqp.
apply Hpqp.
intro Hp.
exfalso.
apply HNp.
assumption.

Qed. (* À vous de finir *)

(* Une série de séquents à prouver; à chaque fois, il faut
   l'énoncer, en introduisant les hypothèses au moyen d'une
   sous-section. *)
Section Exercice_1.
(* P->Q, R->~Q, P->R |- P->S *)
Hypothesis H: P -> Q.
Hypothesis H0: R -> ~Q.
Hypothesis H1: P -> R.
Lemma E1: P -> S.
Proof.

intro Hp.
unfold not in H0.
exfalso.
apply H0.
- apply H1.
  assumption.
- apply H.
  assumption.

Qed.
End Exercice_1.
Section Exercice_2.
(* ~P->~Q |- ~~Q->~~P *)
Hypothesis H: ~P->~Q.
Lemma E2: ~~Q->~~P.
Proof.

intro HNNq.
unfold not.
unfold not in HNNq.
unfold not in H.
intro HNp.
apply H.
- assumption.
- exfalso.
  apply HNNq.
  apply H.
  assumption.

Qed.
End Exercice_2.
Section Exercice_3.
(* P->~P |- ~P *)
Hypothesis H: P->~P.
Lemma E3: ~P.
Proof.

unfold not in H.
unfold not.
intro.
apply H.
- assumption.
- assumption.

Qed.
End Exercice_3.
Section Exercice_4.
(* ~~P |- ~P->~Q *)
Hypothesis H: ~~P.
Lemma E4: ~P->~Q.
Proof.

intro HNp.
intro Hq.
unfold not in H.
unfold not in HNp.
apply H.
assumption.

Qed.
End Exercice_4.
Section Exercice_5.
(* P->~Q, R->Q |- P->~R *)
Hypothesis H: P->~Q.
Hypothesis H0: R->Q.
Lemma E5: P->~R.
Proof.

unfold not in H.
intros Hp Hr.
apply H.
- assumption.
- apply H0.
  assumption.

Qed. 
End Exercice_5.
Section Exercice_6.
(* ~(P->Q) |- ~Q *)
Hypothesis H: ~(P->Q).
Lemma E6: ~Q.
Proof.

intro Hq.
unfold not in H.
apply H.
intro Hp.
assumption.

Qed.
End Exercice_6.
(* Séquents proposés en test par le passé *)

Section Test01.
Hypothesis H: P->Q.

Lemma Ex01: ~(~Q->~P) -> R.
Proof.
intro HNNqNp.
unfold not in HNNqNp.
exfalso.
apply HNNqNp.
intro HNq.
intro Hp.
apply HNq.
apply H.
assumption.
Qed.
End Test01.

Section Test02.
Hypothesis H: ~(P->R).

Lemma Ex02: Q->(P->Q->R)->P.
Proof.
intro Hq.
intro Hpqr.
unfold not in H.
exfalso.
apply H.
intro Hp.
apply Hpqr; assumption; assumption.

Qed.
End Test02.

Section Test03.
Hypothesis H: ~(Q->R).

Lemma Ex03: (P->Q->R)->(P->Q).
Proof.
intros Hpqr Hp.
unfold not in H.
exfalso.
apply H.
intro Hq.
apply Hpqr; assumption; assumption.

Qed.
End Test03.

Section Test04.
Hypothesis H: ~~P.

Lemma Ex04: Q->(P->Q->False)->P.
Proof.
unfold not in H.
intro Hq.
intro HpNq.
exfalso.
apply HpNq.
- exfalso.
  apply H.
  intro Hp.
  apply HpNq; assumption; assumption.
- assumption.
Qed.
End Test04.
    
End Negation.


