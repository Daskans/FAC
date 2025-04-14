Require Import Setoid Classical.

(*  Logique classique
    On peut sauter les 2 commandes suivantes 
 *)

(* un peu de magie noire *)
Definition EXM :=   forall A:Prop, A \/ ~A.

Ltac add_exm A hname:=
  assert(hname : A \/ ~A);[classical_right; assumption|].


Section LK.
(* Pour ajouter une instance du tiers-exclu de la forme  A \/ ~A, 
   avec comme nom H,
   il suffit d'exécuter la tactique "add_exm A H"
*)

Variables P Q R S T : Prop.

Lemma double_neg : ~~ P -> P.
Proof.
intro H.
add_exm  P H0. (* "je fais un tiers exclus sur P " *)
destruct H0 as [H0 | H0]. (* Presque toujours, destruct suit add_exm *)
- assumption.
- assert (f:False).
  {
  apply H; assumption.
  }
destruct f. (* ou: exfalso, etc. *)
Qed.

(* Variantes: tactiques classical_left et classical_right.
   Pour prouver A \/ B:
   - classical_left demande de prouver A, avec ~B comme hypothèse en plus.
   - classigal_right demande de prouver B, avec ~A comme hypothèse en plus.
*)

Lemma weak_exm: P \/ (P->Q).
Proof.
classical_right.
intro p; exfalso; apply H; assumption.
Qed.

(* Exercice: completer toutes les preuves, en remplaçant les
   "Admitted" par des preuves terminées par "Qed."; et 
   sans utiliser ni auto, ni tauto.  *)

Lemma de_morgan_and : ~ ( P /\ Q) <-> ~P \/ ~Q.
Proof.
split.
- intro.
  add_exm P H0.
  destruct H0 as [H0 | H0].
  + add_exm Q H1.
    destruct H1 as [H1 | H1].
    * exfalso.
      apply H.
      split;assumption.
    * classical_right;assumption.
  + classical_left;assumption.
- intro.
  intro.
  destruct H0 as [HP HQ].
  destruct H as [HNP | HNQ].
  + apply HNP;assumption.
  + apply HNQ;assumption.
Qed.

Lemma not_impl_and : ~(P -> Q) <-> P /\ ~ Q.
Proof.
split.
- intro.
  split.
  + add_exm P H0.
    destruct H0 as [H0 | H0].
    assumption.
    exfalso.
    apply H.
    intro.
    exfalso.
    apply H0;assumption.
  + intro.
    apply H.
    intro;assumption.
- intro.
  destruct H as [HP HNQ].
  intro.
  apply HNQ.
  apply H;assumption.
Qed.

Lemma contraposee: (P -> Q) <-> (~Q -> ~P).
Proof.
split.
- intros H H0 H1.
  apply H0.
  apply H;assumption.
- intros.
  add_exm Q H1.
  destruct H1 as [H1 | H1].
  + assumption.
  + exfalso.
    apply H.
    * assumption.
    * assumption.
Qed.

Lemma exm_e : (P -> Q) -> (~P -> Q) -> Q.
Proof.
intros.
add_exm P H1.
destruct H1 as [H1 | H1].
- apply H;assumption.
- apply H0;assumption.
Qed.

Lemma exo_16 : (~ P -> P) -> P.
Proof.
intro.
add_exm P H0.
destruct H0 as [H0 | H0].
- assumption.
- apply H;assumption.
Qed.

Lemma double_impl : (P -> Q) \/ (Q -> P).
Proof.
classical_left.
intro.
add_exm Q H1.
destruct H1 as [H1 | H1].
- assumption.
- exfalso.
  apply H.
  intro.
  assumption.
Qed.

Lemma imp_translation : (P -> Q) <-> ~P \/ Q.
Proof.
split.
- intro.
  add_exm P H0.
  destruct H0 as [H0 | H0].
  + classical_right.
    apply H;assumption.
  + classical_left;assumption.
- intros.
  add_exm Q H1.
  destruct H1 as [H1 |H1].
  + assumption.
  + destruct H as [HNp | Hq].
    * exfalso.
      apply HNp;assumption.
    * assumption. 
Qed.

Lemma Peirce : (( P -> Q) -> P) -> P.
Proof.
intro.
add_exm P H0.
destruct H0 as [H0|H0].
- assumption.
- apply H.
  intro.
  exfalso.
  apply H0;assumption.

Qed.

(* Quelques exercices d'anciens tests *) 
Lemma test_1: (P->Q)->(~P->R)->(R->Q)->Q.
Proof.
intros.
add_exm P H2.
destruct H2 as [H2|H2].
- apply H;assumption.
- apply H1.
  apply H0;assumption.
Qed.

Lemma test__2: (P \/ (Q\/R))-> (~P) -> (~R) -> (P\/Q).
Proof.
intros.
classical_left.
destruct H as [H|H].
- assumption.
- destruct H as [H|H].
  + exfalso.
    apply H2;assumption.
  + exfalso.
    apply H1;assumption.
Qed.

Lemma test_3: (~P-> Q/\R)->(Q->~R)->P.
Proof.
Admitted.

Lemma test_4: (~P->Q)->(~Q\/R)->(P->R)->R.
Proof.
Admitted.

Lemma test_5: (P->Q)->(~P->~Q)->((P/\Q) \/ ~(P\/Q)).
Proof.
Admitted.

Lemma test_6: (P->Q)->(~P->Q)->(Q->R)->R.
Proof.
Admitted.

End LK.

Section Club_Ecossais. (* version propositionnelle *)
Variables E R D M K: Prop.
  (* Ecossais, chaussettes Rouges, sort le Dimanche, Marié, Kilt *)

Hypothesis h1: ~E -> R.
  (* Tout membre non ecossais porte des chaussettes rouges *)
Hypothesis h2: M -> ~D.
  (* Les membres maries ne sortent pas le dimanche *)
Hypothesis h3: D <-> E.
  (* Un membre sort le dimanche si et seulement si il est ecossais *)
Hypothesis h4: K -> E /\ M.
  (* Tout membre qui porte un kilt est ecossais et est marie *)
Hypothesis h5: R -> K.
  (* Tout membre qui porte des chaussettes rouges porte un kilt *)
Hypothesis h6: E -> K.
  (* Tout membre ecossais porte un kilt. *)

Lemma personne: False. (* Le club est vide! *)
Proof.
(* Preuve classique *)
assert (h:K). {
  add_exm E exm.
  destruct exm as [e|ne].
  - apply h6; assumption.
  - apply h5; apply h1; assumption.
  }
assert (hh: E/\M). {
  apply h4; assumption.
  }
destruct hh as [e m].
apply h2.
- assumption.
- rewrite h3; assumption.
Restart.
(* Preuve intuitionniste *)
tauto. (* Au moins on est sûr : tauto ne sait pas faire de tiers exclu *)
Restart.
(* Stratégie: la preuve K fait un tiers exclus sur E; on prouve donc
   ~~(E \/ ~E) *)
assert (h: ~ ~ (E \/ ~E)). {
  intro nTe.
  assert (ne: ~E).  {
    intro e; apply nTe; left; assumption.
    } 
  assert (nne: ~~E). { 
    intro e; apply nTe; right; assumption.
    } 
    apply nne; assumption.
  } (* C'est un peu lourd! Vous pouvez continuer cette preuve, ou repartir de zéro *)
Restart.
(* Encore une autre façon de procéder: commencer par prouver ~~K  *)
Admitted.

End Club_Ecossais.  

(* Au sens strict, cette partie est hors programme; il s'agit de voir que 
   diverses hypothèses (toutes formulées "au second ordre": avec des 
   quantificateurs universels sur des propositions)
   sont équivalentes, et correspondent à la logique classique *)
(* ATTENTION: pour que ces exercices aient un sens, il faut les faire SANS
   utiliser les tactiques réservées à la logique classique (add_exm, ou
   classical_left, ou classical_right *)
Section Second_ordre. 
Definition PEIRCE := forall A B:Prop, ((A -> B) -> A) -> A.
Definition DNEG := forall A, ~~A <-> A.
Definition IMP2OR := forall A B:Prop, (A->B) <-> ~A \/ B.
(* Ce sont des définitions, pas des hypothèses: on ne suppose pas PEIRCE, etc *)

Lemma L2 : IMP2OR -> EXM.
Proof.
unfold IMP2OR, EXM.
intros H A.
assert (h: ~ A \/ A). {
  rewrite <- H. (* Coq "voit" qu'il suffit de prendre B=A; il va falloir prouver A->A *)
Admitted. (* à compléter *)
  
Lemma L3 : EXM -> DNEG.
Proof.
unfold DNEG , EXM.
intros H A.
(* H permet de faire un tiers exclus sur A *)
assert (H0: A \/ ~A).
  {
  admit. (* à remplacer par la bonne preuve (1 tactique suffit!) *)
  }
Admitted. (* à compléter *)

Lemma L4 : PEIRCE -> DNEG.
Proof.
unfold DNEG , PEIRCE.
Admitted. (* à compléter *)
  
Lemma L5 : EXM -> PEIRCE.
Proof.
Admitted. (* à compléter *)

End Second_ordre.


  