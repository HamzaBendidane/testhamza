SET DATEFORMAT YMD
USE [opcaim_extranet]
GO
/****** Object:  Table [dbo].[dgf]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[dgf](
  [id] [int] IDENTITY(1,1) NOT NULL,
  [id_ref_esclave_adefim] [char](25) NULL,
  [t_adefim] [nvarchar](max) NULL,
  [montant_total_pec] [decimal](10, 2) NULL,
  [montant_verse] [decimal](10, 2) NULL,
  [numero_demande] [int] NULL,
  [statut] [int] NOT NULL,
  [statut_paiement] [int] NULL,
  [date_synthese] [datetime] NULL,
  [date_envoi_myopca] [datetime] NULL,
  [date_creation] [datetime] NOT NULL,
  [id_user_creation] [int] NOT NULL,
  [date_last_edit] [datetime] NULL,
  [id_user_last_edit] [int] NULL,
  [date_delete] [datetime] NULL,
  [id_user_delete] [int] NULL,
  [multi_etablissement] [bit] NULL,
  [is_delete] [bit] NOT NULL,
 CONSTRAINT [PK_dgf] PRIMARY KEY CLUSTERED 
(
  [id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[dgf_form_contrat]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[dgf_form_contrat](
  [id] [int] IDENTITY(1,1) NOT NULL,
  [id_dgf] [int] NOT NULL,
  [t_type_contrat] [nvarchar](max) NULL,
  [t_type_contrat_pro] [nvarchar](max) NULL,
  [t_date_debut] [date] NULL,
  [t_date_fin] [date] NULL,
  [t_duree_contrat_mois] [int] NULL,
  [t_duree_essai_jour] [int] NULL,
  [t_duree_hebdo_travail_heure] [int] NULL,
  [t_duree_hebdo_travail_minute] [int] NULL,
  [t_coefficient] [int] NULL,
  [t_convention_collective] [nvarchar](max) NULL,
  [t_groupe] [nvarchar](max) NULL,
  [t_salaire_brut_mensuel] [decimal](10, 2) NULL,
  [t_emploi_occupe] [nvarchar](max) NULL,
  [date_creation] [datetime] NOT NULL,
  [id_user_creation] [int] NOT NULL,
  [date_last_edit] [datetime] NULL,
  [id_user_last_edit] [int] NULL,
  [date_delete] [datetime] NULL,
  [id_user_delete] [int] NULL,
  [is_delete] [bit] NOT NULL,
 CONSTRAINT [PK_t_dgf_form_contrat] PRIMARY KEY CLUSTERED 
(
  [id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

GO
/****** Object:  Table [dbo].[dgf_form_demande]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[dgf_form_demande](
  [id] [int] IDENTITY(1,1) NOT NULL,
  [id_dgf] [int] NOT NULL,
  [t_nature_demande] [nvarchar](max) NOT NULL,
  [t_nature_formation] [nvarchar](max) NULL,
  [date_creation] [datetime] NOT NULL,
  [id_user_creation] [int] NOT NULL,
  [date_last_edit] [datetime] NULL,
  [id_user_last_edit] [int] NULL,
  [date_delete] [datetime] NULL,
  [id_user_delete] [int] NULL,
  [is_delete] [bit] NOT NULL,
 CONSTRAINT [PK_dgf_form_demande] PRIMARY KEY CLUSTERED 
(
  [id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

GO
/****** Object:  Table [dbo].[dgf_form_formation]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[dgf_form_formation](
  [id] [int] IDENTITY(1,1) NOT NULL,
  [id_dgf] [int] NOT NULL,
  [t_finalite_formation] [nvarchar](max) NULL,
  [t_intitule_formation] [nvarchar](max) NULL,
  [t_num_cqpi] [nvarchar](max) NULL,
  [t_saisie_libre_intitule_formation] [nvarchar](max) NULL,
  [t_reference_interne] [nvarchar](max) NULL,
  [t_intitule_finalite] [nvarchar](max) NULL,
  [t_niveau] [nvarchar](max) NULL,
  [t_date_debut] [date] NULL,
  [t_date_fin] [date] NULL,
  [t_date_examen] [date] NULL,
  [t_duree_jours] [int] NULL,
  [t_duree_heures] [int] NULL,
  [t_duree_totale_heure] [int] NULL,
  [t_duree_ens_gen_heure] [int] NULL,
  [t_duree_acc_heure] [int] NULL,
  [t_formation_interne] [bit] NULL,
  [t_attestation_formation_interne] [bit] NULL,
  [t_nb_participant] [int] NULL,
  [t_formation_intra_entreprise] [bit] NULL,
  [t_specialite] [nvarchar](max) NULL,
  [date_creation] [datetime] NOT NULL,
  [id_user_creation] [int] NOT NULL,
  [date_last_edit] [datetime] NULL,
  [id_user_last_edit] [int] NULL,
  [date_delete] [datetime] NULL,
  [id_user_delete] [int] NULL,
  [is_delete] [bit] NOT NULL,
 CONSTRAINT [PK_t_dgf_form_formation] PRIMARY KEY CLUSTERED 
(
  [id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

GO
/****** Object:  Table [dbo].[dgf_form_formation_repartition]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[dgf_form_formation_repartition](
  [id] [int] IDENTITY(1,1) NOT NULL,
  [id_dgf_form_formation] [int] NOT NULL,
  [t_annee] [int] NULL,
  [t_repartition_heure] [int] NULL,
  [date_creation] [datetime] NOT NULL,
  [id_user_creation] [int] NOT NULL,
  [date_last_edit] [datetime] NULL,
  [id_user_last_edit] [int] NULL,
  [date_delete] [datetime] NULL,
  [id_user_delete] [int] NULL,
  [is_delete] [bit] NOT NULL,
 CONSTRAINT [PK_dgf_form_formation_repartition_1] PRIMARY KEY CLUSTERED 
(
  [id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[dgf_form_justificatif]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[dgf_form_justificatif](
  [id] [int] IDENTITY(1,1) NOT NULL,
  [id_dgf] [int] NOT NULL,
  [t_fichier] [nvarchar](max) NULL,
  [t_chemin_fichier] [nvarchar](max) NULL,
  [t_nom_ref_fichier] [nvarchar](max) NULL,
  [t_nom_fichier] [nvarchar](max) NULL,
  [t_repertoire_fichier] [nvarchar](max) NULL,
  [t_obligatoire] [bit] NULL,
  [t_extension_fichier] [nchar](10) NULL,
  [date_creation] [datetime] NOT NULL,
  [id_user_creation] [int] NOT NULL,
  [date_last_edit] [datetime] NULL,
  [id_user_last_edit] [int] NULL,
  [date_delete] [datetime] NULL,
  [id_user_delete] [int] NULL,
  [is_delete] [bit] NOT NULL,
 CONSTRAINT [PK_t_dgf_justificatif] PRIMARY KEY CLUSTERED 
(
  [id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

GO
/****** Object:  Table [dbo].[dgf_form_justificatif_paiement]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[dgf_form_justificatif_paiement](
  [id] [int] IDENTITY(1,1) NOT NULL,
  [id_dgf] [int] NOT NULL,
  [t_fichier] [nvarchar](max) NULL,
  [t_chemin_fichier] [nvarchar](max) NULL,
  [t_nom_ref_fichier] [nvarchar](max) NULL,
  [t_nom_fichier] [nvarchar](max) NULL,
  [t_repertoire_fichier] [nvarchar](max) NULL,
  [t_obligatoire] [bit] NULL,
  [t_extension_fichier] [nchar](10) NULL,
  [date_creation] [date] NOT NULL,
  [id_user_creation] [int] NOT NULL,
  [date_last_edit] [date] NULL,
  [id_user_last_edit] [int] NULL,
  [date_delete] [date] NULL,
  [id_user_delete] [int] NULL,
  [is_delete] [bit] NOT NULL,
 CONSTRAINT [PK_t_dgf_justificatif_paiement] PRIMARY KEY CLUSTERED 
(
  [id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

GO
/****** Object:  Table [dbo].[dgf_form_organisme_formation]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[dgf_form_organisme_formation](
  [id] [int] IDENTITY(1,1) NOT NULL,
  [id_dgf] [int] NOT NULL,
  [t_siret] [nvarchar](max) NULL,
  [t_numero_declaration] [nvarchar](max) NULL,
  [t_raison_sociale] [nvarchar](max) NULL,
  [t_numero_adresse] [nvarchar](max) NULL,
  [t_rue] [nvarchar](max) NULL,
  [t_complement_rue] [nvarchar](max) NULL,
  [t_code_postal] [nvarchar](max) NULL,
  [t_ville] [nvarchar](max) NULL,
  [t_pays] [nvarchar](max) NULL,
  [t_telephone] [nvarchar](max) NULL,
  [t_email] [nvarchar](max) NULL,
  [t_assujetti_tva] [bit] NULL,
  [t_numero_tva] [nvarchar](max) NULL,
  [t_contact_nom] [nvarchar](max) NULL,
  [t_contact_prenom] [nvarchar](max) NULL,
  [t_contact_fonction] [nvarchar](max) NULL,
  [t_contact_email] [nvarchar](max) NULL,
  [t_contact_telephone] [nvarchar](max) NULL,
  [t_cout_pedagogique] [decimal](10, 2) NULL,
  [t_evaluation_preformative] [decimal](10, 2) NULL,
  [t_passage_certification] [decimal](10, 2) NULL,
  [t_paiement_direct] [bit] NULL,
  [t_cout_prestation] [decimal](10, 2) NULL,
  [t_ratio_cout_duree] [decimal](10, 2) NULL,
  [date_creation] [datetime] NOT NULL,
  [id_user_creation] [int] NOT NULL,
  [date_last_edit] [datetime] NULL,
  [id_user_last_edit] [int] NULL,
  [date_delete] [datetime] NULL,
  [id_user_delete] [int] NULL,
  [is_delete] [bit] NOT NULL,
 CONSTRAINT [PK_t_dgf_form_organisme_formation_1] PRIMARY KEY CLUSTERED 
(
  [id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

GO
/****** Object:  Table [dbo].[dgf_form_salarie]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[dgf_form_salarie](
  [id] [int] IDENTITY(1,1) NOT NULL,
  [id_dgf] [int] NOT NULL,
  [t_entreprise] [nvarchar](max) NULL,
  [t_entreprise_numero_rue] [nvarchar](max) NULL,
  [t_entreprise_rue] [nvarchar](max) NULL,
  [t_entreprise_complement_rue] [nvarchar](max) NULL,
  [t_entreprise_code_postal] [int] NULL,
  [t_entreprise_ville] [nvarchar](max) NULL,
  [t_entreprise_telephone] [nvarchar](max) NULL,
  [t_entreprise_fax] [nvarchar](max) NULL,
  [t_entreprise_email] [nvarchar](max) NULL,
  [t_nom] [nvarchar](max) NULL,
  [t_prenom] [nvarchar](max) NULL,
  [t_date_naissance] [date] NULL,
  [t_age] [int] NULL,
  [t_sexe] [bit] NULL,
  [t_travailleur_handicape] [bit] NULL,
  [t_numero_rue] [nvarchar](max) NULL,
  [t_rue] [nvarchar](max) NULL,
  [t_complement_rue] [nvarchar](max) NULL,
  [t_code_postal] [int] NULL,
  [t_ville] [nvarchar](max) NULL,
  [t_telephone] [nvarchar](max) NULL,
  [t_email] [nvarchar](max) NULL,
  [t_derniere_situation] [nvarchar](max) NULL,
  [t_caisse_retraite] [nvarchar](max) NULL,
  [t_caisse_prevoyance] [nvarchar](max) NULL,
  [t_diplome] [nvarchar](max) NULL,
  [t_beneficiaire_minimas_sociaux] [nvarchar](max) NULL,
  [t_numero_pole_emploi] [nvarchar](max) NULL,
  [t_nombre_mois_inscrit_pole_emploi] [int] NULL,
  [t_salaire_horaire_brut] [decimal](10, 2) NULL,
  [t_salaire_horaire_net] [decimal](10, 2) NULL,
  [t_cout_pedagogique] [decimal](10, 2) NULL,
  [t_cout_evaluation_preformative] [decimal](10, 2) NULL,
  [t_frais_transport] [decimal](10, 2) NULL,
  [t_frais_repas] [decimal](10, 2) NULL,
  [t_nb_repas] [int] NULL,
  [t_frais_nuitee] [decimal](10, 2) NULL,
  [t_nb_nuitee] [int] NULL,
  [t_mobilisation_cpf] [bit] NULL,
  [t_heure_cpf] [int] NULL,
  [t_numero_securite_sociale] [nvarchar](max) NULL,
  [t_duree_action] [decimal](10, 2) NULL,
  [t_duree_action_tt] [decimal](10, 2) NULL,
  [t_duree_action_htt] [decimal](10, 2) NULL,
  [t_duree_eval_preformative_heure] [int] NULL,
  [t_duree_eval_preformative_minute] [int] NULL,
  [t_particularite] [nvarchar](max) NULL,
  [date_creation] [datetime] NOT NULL,
  [id_user_creation] [int] NOT NULL,
  [date_last_edit] [datetime] NULL,
  [id_user_last_edit] [int] NULL,
  [date_delete] [datetime] NULL,
  [id_user_delete] [int] NULL,
  [is_delete] [bit] NOT NULL,
 CONSTRAINT [PK_t_dgf_form_salarie] PRIMARY KEY CLUSTERED 
(
  [id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

GO
/****** Object:  Table [dbo].[dgf_form_tuteur]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[dgf_form_tuteur](
  [id] [int] IDENTITY(1,1) NOT NULL,
  [id_dgf] [int] NOT NULL,
  [t_etablissement] [nvarchar](max) NULL,
  [t_nom] [nvarchar](max) NULL,
  [t_prenom] [nvarchar](max) NULL,
  [t_telephone] [nvarchar](max) NULL,
  [t_email] [nvarchar](max) NULL,
  [t_date_naissance] [date] NULL,
  [t_emploi] [nvarchar](max) NULL,
  [t_diplome] [nvarchar](max) NULL,
  [t_nb_salarie_encadre] [int] NULL,
  [t_formation_tuteur] [bit] NOT NULL,
  [t_date_formation] [date] NULL,
  [t_duree_formation] [int] NULL,
  [t_nom_organisme] [nvarchar](max) NULL,
  [t_certif_role_tuteur] [bit] NULL,
  [t_certif_deux_ans_exp] [bit] NULL,
  [date_creation] [datetime] NOT NULL,
  [id_user_creation] [int] NOT NULL,
  [date_last_edit] [datetime] NULL,
  [id_user_last_edit] [int] NULL,
  [date_delete] [datetime] NULL,
  [id_user_delete] [int] NULL,
  [is_delete] [bit] NOT NULL,
 CONSTRAINT [PK_t_dgf_form_tuteur] PRIMARY KEY CLUSTERED 
(
  [id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

GO
/****** Object:  Table [dbo].[dgf_paiement]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[dgf_paiement](
  [id] [int] IDENTITY(1,1) NOT NULL,
  [id_dgf] [int] NULL,
  [montant] [decimal](10, 2) NULL,
  [date_creation] [datetime] NOT NULL,
  [id_user_creation] [int] NOT NULL,
  [date_last_edit] [datetime] NULL,
  [id_user_last_edit] [int] NULL,
  [date_delete] [datetime] NULL,
  [id_user_delete] [int] NULL,
  [is_delete] [bit] NOT NULL,
 CONSTRAINT [PK_dgf_paiement] PRIMARY KEY CLUSTERED 
(
  [id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[drupal_user]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[drupal_user](
  [id] [int] IDENTITY(1,1) NOT NULL,
  [civilite] [smallint] NULL,
  [name] [nvarchar](max) NULL,
  [password] [nvarchar](max) NULL,
  [mail] [nvarchar](max) NULL,
  [fonction] [nvarchar](max) NULL,
  [telephone] [nvarchar](max) NULL,
  [date_creation] [date] NOT NULL,
  [id_user_creation] [int] NOT NULL,
  [date_last_edit] [date] NULL,
  [id_user_last_edit] [int] NULL,
  [date_delete] [date] NULL,
  [id_user_delete] [int] NULL,
  [is_delete] [bit] NOT NULL,
  [id_user_drupal] [int] NOT NULL,
 CONSTRAINT [PK_drupal_user] PRIMARY KEY CLUSTERED 
(
  [id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

GO
/****** Object:  Table [dbo].[habilitation]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[habilitation](
  [cle] [char](20) NOT NULL,
  [libelle] [nvarchar](max) NOT NULL,
 CONSTRAINT [PK_habilitation] PRIMARY KEY CLUSTERED 
(
  [cle] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[lien_dgf_ref_esclave_entreprise]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[lien_dgf_ref_esclave_entreprise](
  [id] [int] IDENTITY(1,1) NOT NULL,
  [id_dgf] [int] NOT NULL,
  [id_ref_esclave_entreprise] [char](25) NOT NULL,
  [t_numero_adherent] [nvarchar](max) NULL,
  [t_raison_sociale] [nvarchar](max) NULL,
  [t_siret] [nvarchar](max) NULL,
  [t_nom_demandeur] [nvarchar](max) NULL,
  [numero_myopca] [int] NULL,
  [date_creation] [datetime] NOT NULL,
  [id_user_creation] [int] NOT NULL,
  [date_last_edit] [datetime] NULL,
  [id_user_last_edit] [int] NULL,
  [date_delete] [datetime] NULL,
  [id_user_delete] [int] NULL,
  [is_delete] [bit] NOT NULL,
  [t_entreprise_ville] [nvarchar](max) NULL,
  [t_code_naf] [nvarchar](max) NULL,
  [t_convention_collective] [nvarchar](max) NULL,
  [t_effectif] [nvarchar](max) NULL,
  [t_code_idcc] [nvarchar](max) NULL,
 CONSTRAINT [PK_lien_dgf_ref_esclave_entreprise] PRIMARY KEY CLUSTERED 
(
  [id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[lien_drupal_user_habilitation]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[lien_drupal_user_habilitation](
  [id_drupal_user] [int] NOT NULL,
  [id_habilitation] [char](20) NOT NULL,
 CONSTRAINT [PK_lien_drupal_user_habilitation] PRIMARY KEY CLUSTERED 
(
  [id_drupal_user] ASC,
  [id_habilitation] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[lien_ref_finalite_formation_nature_demande]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[lien_ref_finalite_formation_nature_demande](
  [id_ref_nature_demande] [int] NOT NULL,
  [id_ref_finalite_formation] [int] NOT NULL
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[lien_ref_nature_demande_ref_justificatif]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[lien_ref_nature_demande_ref_justificatif](
  [id_ref_nature_demande] [int] NOT NULL,
  [id_ref_justificatif] [int] NOT NULL
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[lien_ref_nature_demande_ref_nature_formation]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[lien_ref_nature_demande_ref_nature_formation](
  [id_ref_nature_demande] [int] NOT NULL,
  [id_ref_nature_formation] [int] NOT NULL
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[lien_user_autre_entreprise]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[lien_user_autre_entreprise](
  [id_user_autre] [int] NOT NULL,
  [id_ref_esclave_entreprise] [char](25) NOT NULL,
  [est_actif] [bit] NOT NULL,
  [est_valide] [bit] NOT NULL,
 CONSTRAINT [PK_lien_user_autre_entreprise] PRIMARY KEY CLUSTERED 
(
  [id_user_autre] ASC,
  [id_ref_esclave_entreprise] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[lien_user_entreprise_ref_esclave_entreprise]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[lien_user_entreprise_ref_esclave_entreprise](
  [id_user_entreprise] [int] NOT NULL,
  [id_ref_esclave_entreprise] [char](25) NOT NULL,
  [est_valide] [bit] NOT NULL,
  [est_actif] [bit] NOT NULL,
 CONSTRAINT [PK_lien_user_entreprise_ref_esclave_entreprise] PRIMARY KEY CLUSTERED 
(
  [id_user_entreprise] ASC,
  [id_ref_esclave_entreprise] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[logs]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[logs](
  [id] [int] NOT NULL,
  [date] [datetime] NOT NULL,
  [adresse_ip] [nchar](10) NOT NULL,
  [id_user] [int] NOT NULL,
  [description] [nvarchar](max) NOT NULL,
  [type_objet] [nvarchar](max) NULL,
  [id_object] [int] NULL,
 CONSTRAINT [PK_logs] PRIMARY KEY CLUSTERED 
(
  [id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

GO
/****** Object:  Table [dbo].[ref_beneficiaire_minimas_sociaux]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ref_beneficiaire_minimas_sociaux](
  [id] [int] IDENTITY(1,1) NOT NULL,
  [code] [nchar](10) NOT NULL,
  [label] [nvarchar](max) NOT NULL,
  [date_creation] [datetime] NOT NULL,
  [id_user_creation] [int] NOT NULL,
  [date_last_edit] [datetime] NULL,
  [id_user_last_edit] [int] NULL,
  [date_delete] [datetime] NULL,
  [id_user_delete] [int] NULL,
  [is_delete] [bit] NOT NULL CONSTRAINT [DF_ref_beneficiaire_minimas_sociaux_is_delete]  DEFAULT ((0)),
 CONSTRAINT [PK_ref_beneficiaire_minimas_sociaux] PRIMARY KEY CLUSTERED 
(
  [id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

GO
/****** Object:  Table [dbo].[ref_derniere_situation]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ref_derniere_situation](
  [id] [int] IDENTITY(1,1) NOT NULL,
  [code] [nchar](10) NOT NULL,
  [label] [nvarchar](max) NOT NULL,
  [date_creation] [datetime] NOT NULL,
  [id_user_creation] [int] NOT NULL,
  [date_last_edit] [datetime] NULL,
  [id_user_last_edit] [int] NULL,
  [date_delete] [datetime] NULL,
  [id_user_delete] [int] NULL,
  [is_delete] [bit] NOT NULL CONSTRAINT [DF_ref_derniere_situation_is_delete]  DEFAULT ((0)),
 CONSTRAINT [PK_ref_derniere_situation] PRIMARY KEY CLUSTERED 
(
  [id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

GO
/****** Object:  Table [dbo].[ref_diplome]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ref_diplome](
  [id] [int] IDENTITY(1,1) NOT NULL,
  [code] [nchar](10) NULL,
  [label] [nvarchar](max) NOT NULL,
  [date_creation] [datetime] NOT NULL,
  [id_user_creation] [int] NOT NULL,
  [date_last_edit] [datetime] NULL,
  [id_user_last_edit] [int] NULL,
  [date_delete] [datetime] NULL,
  [id_user_delete] [int] NULL,
  [is_delete] [bit] NOT NULL CONSTRAINT [DF_ref_diplome_is_delete]  DEFAULT ((0)),
 CONSTRAINT [PK_ref_diplome] PRIMARY KEY CLUSTERED 
(
  [id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

GO
/****** Object:  Table [dbo].[ref_finalite_formation]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ref_finalite_formation](
  [id] [int] IDENTITY(1,1) NOT NULL,
  [code] [nchar](10) NOT NULL,
  [label] [nvarchar](max) NOT NULL,
  [date_creation] [datetime] NOT NULL,
  [id_user_creation] [int] NOT NULL,
  [date_last_edit] [datetime] NULL,
  [id_user_last_edit] [int] NULL,
  [date_delete] [datetime] NULL,
  [id_user_delete] [int] NULL,
  [is_delete] [bit] NOT NULL CONSTRAINT [DF_ref_intitulé_formation_is_delete]  DEFAULT ((0)),
 CONSTRAINT [PK_ref_intitulé_formation] PRIMARY KEY CLUSTERED 
(
  [id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

GO
/****** Object:  Table [dbo].[ref_groupe]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ref_groupe](
  [id] [int] IDENTITY(1,1) NOT NULL,
  [code] [nchar](10) NULL,
  [label] [nvarchar](max) NOT NULL,
  [date_creation] [datetime] NOT NULL,
  [id_user_creation] [int] NOT NULL,
  [date_last_edit] [datetime] NULL,
  [id_user_last_edit] [int] NULL,
  [date_delete] [datetime] NULL,
  [id_user_delete] [int] NULL,
  [is_delete] [bit] NOT NULL CONSTRAINT [DF_ref_groupe_is_delete]  DEFAULT ((0)),
 CONSTRAINT [PK_ref_groupe] PRIMARY KEY CLUSTERED 
(
  [id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

GO
/****** Object:  Table [dbo].[ref_justificatif]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ref_justificatif](
  [id] [int] IDENTITY(1,1) NOT NULL,
  [code] [nchar](10) NULL,
  [label] [nvarchar](max) NOT NULL,
  [date_creation] [datetime] NOT NULL,
  [id_user_creation] [int] NOT NULL,
  [date_last_edit] [datetime] NULL,
  [id_user_last_edit] [int] NULL,
  [date_delete] [datetime] NULL,
  [id_user_delete] [int] NULL,
  [is_delete] [bit] NOT NULL CONSTRAINT [DF_ref_justificatif_is_delete]  DEFAULT ((0)),
  [id_ref_nature_demande] [int] NULL,
  [is_mandatory] [bit] NULL,
 CONSTRAINT [PK_ref_justificatif] PRIMARY KEY CLUSTERED 
(
  [id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

GO
/****** Object:  Table [dbo].[ref_nature_demande]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ref_nature_demande](
  [id] [int] IDENTITY(1,1) NOT NULL,
  [label] [nvarchar](max) NOT NULL,
  [date_creation] [datetime] NOT NULL,
  [id_user_creation] [int] NOT NULL,
  [date_last_edit] [datetime] NULL,
  [id_user_last_edit] [int] NULL,
  [date_delete] [datetime] NULL,
  [id_user_delete] [int] NULL,
  [is_delete] [bit] NOT NULL CONSTRAINT [DF_ref_nature_demande_is_delete]  DEFAULT ((0)),
 CONSTRAINT [PK_ref_nature_demande] PRIMARY KEY CLUSTERED 
(
  [id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

GO
/****** Object:  Table [dbo].[ref_nature_formation]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ref_nature_formation](
  [id] [int] IDENTITY(1,1) NOT NULL,
  [label] [nvarchar](max) NOT NULL,
  [date_creation] [datetime] NOT NULL,
  [id_user_creation] [int] NOT NULL,
  [date_last_edit] [datetime] NULL,
  [id_user_last_edit] [int] NULL,
  [date_delete] [datetime] NULL,
  [id_user_delete] [int] NULL,
  [is_delete] [bit] NOT NULL CONSTRAINT [DF_ref_nature_formation_is_delete]  DEFAULT ((0)),
 CONSTRAINT [PK_ref_nature_formation] PRIMARY KEY CLUSTERED 
(
  [id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

GO
/****** Object:  Table [dbo].[ref_nomenclature_fichier_reporting]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ref_nomenclature_fichier_reporting](
  [id] [int] IDENTITY(1,1) NOT NULL,
  [nom] [nvarchar](max) NOT NULL,
  [pattern_fichier] [nvarchar](max) NOT NULL,
  [date_creation] [datetime] NOT NULL,
  [id_user_creation] [int] NOT NULL,
  [date_last_edit] [datetime] NULL,
  [id_user_last_edit] [int] NULL,
  [date_delete] [datetime] NULL,
  [id_user_delete] [int] NULL,
  [is_delete] [bit] NOT NULL,
 CONSTRAINT [PK_ref_nomenclature_fichier_reporting] PRIMARY KEY CLUSTERED 
(
  [id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

GO
/****** Object:  Table [dbo].[ref_params]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ref_params](
  [id] [int] IDENTITY(1,1) NOT NULL,
  [code] [nchar](10) NOT NULL,
  [label] [nvarchar](max) NOT NULL,
  [date_creation] [datetime] NOT NULL,
  [id_user_creation] [int] NOT NULL,
  [date_last_edit] [datetime] NULL,
  [id_user_last_edit] [int] NULL,
  [date_delete] [datetime] NULL,
  [id_user_delete] [int] NULL,
  [is_delete] [bit] NOT NULL
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

GO
/****** Object:  Table [dbo].[ref_type_contrat]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ref_type_contrat](
  [id] [int] IDENTITY(1,1) NOT NULL,
  [label] [nvarchar](max) NOT NULL,
  [date_creation] [datetime] NOT NULL,
  [id_user_creation] [int] NOT NULL,
  [date_last_edit] [datetime] NULL,
  [id_user_last_edit] [int] NULL,
  [date_delete] [datetime] NULL,
  [id_user_delete] [int] NULL,
  [is_delete] [bit] NOT NULL,
  [parent] [int] NULL,
  [code] [nchar](10) NULL,
 CONSTRAINT [PK_ref_type_contrat] PRIMARY KEY CLUSTERED 
(
  [id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

GO
/****** Object:  Table [dbo].[temp_dgf_form_contrat]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[temp_dgf_form_contrat](
  [id] [int] IDENTITY(1,1) NOT NULL,
  [id_dgf] [int] NOT NULL,
  [id_ref_type_contrat] [int] NULL,
  [id_ref_esclave_type_contrat] [char](25) NULL,
  [id_ref_esclave_convention_collective] [char](25) NULL,
  [id_ref_groupe] [int] NULL,
  [date_debut] [date] NULL,
  [date_fin] [date] NULL,
  [duree_contrat_mois] [int] NULL,
  [duree_essai_jour] [int] NULL,
  [duree_hebdo_travail_heure] [int] NULL,
  [duree_hebdo_travail_minute] [int] NULL,
  [coefficient] [int] NULL,
  [salaire_brut_mensuel] [decimal](10, 2) NULL,
  [emploi_occupe] [nvarchar](max) NULL,
  [date_creation] [datetime] NOT NULL,
  [id_user_creation] [int] NOT NULL,
  [date_last_edit] [datetime] NULL,
  [id_user_last_edit] [int] NULL,
  [date_delete] [datetime] NULL,
  [id_user_delete] [int] NULL,
  [is_delete] [bit] NOT NULL,
  [niveau] [int] NULL,
 CONSTRAINT [PK_dgf_form_contrat] PRIMARY KEY CLUSTERED 
(
  [id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[temp_dgf_form_demande]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[temp_dgf_form_demande](
  [id] [int] IDENTITY(1,1) NOT NULL,
  [id_dgf] [int] NOT NULL,
  [id_dgf_nature_demande] [int] NOT NULL,
  [id_dgf_nature_formation] [int] NULL,
 CONSTRAINT [PK_temp_dgf_form_demande] PRIMARY KEY CLUSTERED 
(
  [id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[temp_dgf_form_formation]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[temp_dgf_form_formation](
  [id] [int] IDENTITY(1,1) NOT NULL,
  [id_dgf] [int] NOT NULL,
  [id_ref_finalite_formation] [int] NULL,
  [id_ref_esclave_intitule_formation] [char](25) NULL,
  [id_ref_esclave_niveau] [char](25) NULL,
  [id_ref_esclave_specialite] [char](25) NULL,
  [intitule_finalite] [nvarchar](max) NULL,
  [intitule_formation] [nvarchar](max) NULL,
  [num_cqpi] [int] NULL,
  [reference_interne] [nvarchar](max) NULL,
  [formation_interne] [bit] NULL,
  [date_debut] [date] NULL,
  [date_fin] [date] NULL,
  [date_examen] [date] NULL,
  [duree_jours] [int] NULL,
  [duree_heures] [int] NULL,
  [duree_totale_heure] [int] NULL,
  [duree_ens_gen_heure] [int] NULL,
  [duree_acc_heure] [int] NULL,
  [nb_participant] [int] NULL,
  [formation_intra_entreprise] [bit] NULL,
  [date_creation] [datetime] NOT NULL,
  [id_user_creation] [int] NOT NULL,
  [date_last_edit] [datetime] NULL,
  [id_user_last_edit] [int] NULL,
  [date_delete] [datetime] NULL,
  [id_user_delete] [int] NULL,
  [is_delete] [bit] NOT NULL,
 CONSTRAINT [PK_dgf_form_formation] PRIMARY KEY CLUSTERED 
(
  [id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[temp_dgf_form_formation_repartition]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[temp_dgf_form_formation_repartition](
  [id] [int] IDENTITY(1,1) NOT NULL,
  [id_dgf_form_formation] [int] NULL,
  [annee] [int] NULL,
  [repartition_heure] [int] NULL,
 CONSTRAINT [PK_dgf_form_formation_repartition] PRIMARY KEY CLUSTERED 
(
  [id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[temp_dgf_form_justificatif]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[temp_dgf_form_justificatif](
  [id] [int] IDENTITY(1,1) NOT NULL,
  [id_dgf] [int] NOT NULL,
  [id_ref_justificatifs] [int] NULL,
  [nom_fichier] [nvarchar](max) NULL,
  [chemin_fichier] [nvarchar](max) NULL,
  [repertoire_fichier] [nvarchar](max) NULL,
  [date_creation] [datetime] NOT NULL,
  [id_user_creation] [int] NOT NULL,
  [date_last_edit] [datetime] NULL,
  [id_user_last_edit] [int] NULL,
  [date_delete] [datetime] NULL,
  [id_user_delete] [int] NULL,
  [is_delete] [bit] NOT NULL,
 CONSTRAINT [PK_dgf_form_justificatif] PRIMARY KEY CLUSTERED 
(
  [id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

GO
/****** Object:  Table [dbo].[temp_dgf_form_justificatif_paiement]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[temp_dgf_form_justificatif_paiement](
  [id] [int] IDENTITY(1,1) NOT NULL,
  [id_dgf] [int] NOT NULL,
  [id_ref_justificatifs] [int] NULL,
  [nom_fichier] [nvarchar](max) NULL,
  [chemin_fichier] [nvarchar](max) NULL,
  [obligatoire] [bit] NULL,
  [extension_fichier] [nchar](10) NULL,
  [date_creation] [datetime] NOT NULL,
  [id_user_creation] [int] NOT NULL,
  [date_last_edit] [datetime] NULL,
  [id_user_last_edit] [int] NULL,
  [date_delete] [datetime] NULL,
  [id_user_delete] [int] NULL,
  [is_delete] [bit] NOT NULL,
 CONSTRAINT [PK_dgf_form_justificatif_paiement] PRIMARY KEY CLUSTERED 
(
  [id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

GO
/****** Object:  Table [dbo].[temp_dgf_form_organisme_formation]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[temp_dgf_form_organisme_formation](
  [id] [int] IDENTITY(1,1) NOT NULL,
  [id_dgf] [int] NOT NULL,
  [id_ref_esclave_organisme_formation] [char](25) NOT NULL,
  [id_ref_esclave_contacts_organisme_formation] [char](25) NULL,
  [cout_pedagogique] [decimal](10, 2) NULL,
  [evaluation_preformative] [decimal](10, 2) NULL,
  [passage_certification] [decimal](10, 2) NULL,
  [cout_prestation] [decimal](10, 2) NULL,
  [ratio_cout_duree] [decimal](10, 2) NULL,
  [paiement_direct] [bit] NULL,
  [date_creation] [datetime] NOT NULL,
  [id_user_creation] [int] NOT NULL,
  [date_last_edit] [datetime] NULL,
  [id_user_last_edit] [int] NULL,
  [date_delete] [datetime] NULL,
  [id_user_delete] [int] NULL,
  [is_delete] [bit] NOT NULL,
 CONSTRAINT [PK_dgf_form_organisme_formation] PRIMARY KEY CLUSTERED 
(
  [id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[temp_dgf_form_salarie]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[temp_dgf_form_salarie](
  [id] [int] IDENTITY(1,1) NOT NULL,
  [id_dgf] [int] NOT NULL,
  [id_ref_esclave_salarie] [char](25) NOT NULL,
  [id_ref_esclave_entreprise] [char](25) NULL,
  [id_ref_esclave_particularites] [char](25) NULL,
  [id_ref_beneficiaire_minimas_sociaux] [int] NULL,
  [id_ref_derniere_situation] [int] NULL,
  [id_ref_diplome] [int] NULL,
  [salaire_horaire_brut] [decimal](10, 2) NULL,
  [salaire_horaire_net] [decimal](10, 2) NULL,
  [cout_pedagogique] [decimal](10, 2) NULL,
  [cout_evaluation_preformative] [decimal](10, 2) NULL,
  [frais_transport] [decimal](10, 2) NULL,
  [frais_repas] [decimal](10, 2) NULL,
  [nb_repas] [int] NULL,
  [frais_nuitee] [decimal](10, 2) NULL,
  [nb_nuitee] [int] NULL,
  [mobilisation_cpf] [bit] NULL,
  [heure_cpf] [int] NULL,
  [numero_securite_sociale] [nvarchar](max) NULL,
  [duree_action] [decimal](10, 2) NULL,
  [duree_action_tt] [decimal](10, 2) NULL,
  [duree_action_htt] [decimal](10, 2) NULL,
  [duree_eval_preformative_heure] [int] NULL,
  [duree_eval_preformative_minute] [int] NULL,
  [date_creation] [datetime] NOT NULL,
  [id_user_creation] [int] NOT NULL,
  [date_last_edit] [datetime] NULL,
  [id_user_last_edit] [int] NULL,
  [date_delete] [datetime] NULL,
  [id_user_delete] [int] NULL,
  [is_delete] [bit] NOT NULL,
  [numero_rue] [nvarchar](max) NULL,
  [nom_rue] [nvarchar](max) NULL,
  [complement_adresse] [nvarchar](max) NULL,
  [code_postal] [nvarchar](max) NULL,
  [ville] [nvarchar](max) NULL,
  [telephone] [nvarchar](max) NULL,
  [email] [nvarchar](max) NULL,
  [numero_inscrit_pole_emploi] [nvarchar](max) NULL,
  [nombre_mois_inscrit_pole_emploi] [nvarchar](max) NULL,
  [caisse_retraite] [nvarchar](max) NULL,
  [caisse_prevoyance] [nvarchar](max) NULL,
 CONSTRAINT [PK_dgf_form_salarie] PRIMARY KEY CLUSTERED 
(
  [id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[temp_dgf_form_tuteur]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[temp_dgf_form_tuteur](
  [id] [int] IDENTITY(1,1) NOT NULL,
  [id_dgf] [int] NOT NULL,
  [id_ref_esclave_salarie] [char](25) NULL,
  [id_ref_esclave_entreprise] [char](25) NULL,
  [id_ref_diplome] [int] NULL,
  [nb_salarie_encadre] [int] NULL,
  [emploi] [nvarchar](max) NULL,
  [formation_tuteur] [bit] NOT NULL,
  [date_formation] [date] NULL,
  [duree_formation] [int] NULL,
  [nom_organisme] [nvarchar](max) NULL,
  [certif_role_tuteur] [bit] NULL,
  [certif_deux_ans_exp] [bit] NULL,
  [date_creation] [datetime] NOT NULL,
  [id_user_creation] [int] NOT NULL,
  [date_last_edit] [datetime] NULL,
  [id_user_last_edit] [int] NULL,
  [date_delete] [datetime] NULL,
  [id_user_delete] [int] NULL,
  [is_delete] [bit] NOT NULL,
  [telephone] [nvarchar](max) NULL,
  [email] [nvarchar](max) NULL,
 CONSTRAINT [PK_dgf_form_tuteur] PRIMARY KEY CLUSTERED 
(
  [id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[user_autre]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[user_autre](
  [id] [int] NOT NULL,
  [id_drupal_user] [int] NOT NULL,
 CONSTRAINT [PK_user_autre] PRIMARY KEY CLUSTERED 
(
  [id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[user_entreprise]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[user_entreprise](
  [id] [int] IDENTITY(1,1) NOT NULL,
  [id_user_responsable] [int] NULL,
  [numero_demande] [int] NULL,
  [charte_signe] [bit] NULL,
  [date_charte_signe] [date] NULL,
  [id_drupal_user] [int] NOT NULL,
 CONSTRAINT [PK_user_entreprise] PRIMARY KEY CLUSTERED 
(
  [id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[user_organisme_formation]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[user_organisme_formation](
  [id] [int] NOT NULL,
  [id_ref_esclave_organisme_formation] [char](25) NULL,
  [id_user_responsable] [int] NULL,
  [numero_demande] [int] NULL,
  [charte_signe] [bit] NULL,
  [date_charte_signe] [date] NULL,
  [id_drupal_user] [int] NOT NULL,
 CONSTRAINT [PK_user_organisme_formation] PRIMARY KEY CLUSTERED 
(
  [id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[user_responsable]    Script Date: 01/06/2015 10:50:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[user_responsable](
  [id] [int] IDENTITY(1,1) NOT NULL,
  [civilite] [bit] NULL,
  [nom] [nvarchar](max) NULL,
  [prenom] [nvarchar](max) NULL,
  [email] [nvarchar](max) NULL,
  [fonction] [nvarchar](max) NULL,
 CONSTRAINT [PK_user_responsable] PRIMARY KEY CLUSTERED 
(
  [id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

GO
INSERT [dbo].[habilitation] ([cle], [libelle]) VALUES (N'ACC_REP             ', N'Accéder aux reporting')
GO
INSERT [dbo].[habilitation] ([cle], [libelle]) VALUES (N'GES_CON_FPC         ', N'Gérer les contributions FPC (formation professionnelle continue)')
GO
INSERT [dbo].[habilitation] ([cle], [libelle]) VALUES (N'GES_CON_TA          ', N'Gérer les contributions TA (taxe apprentissage)')
GO
INSERT [dbo].[habilitation] ([cle], [libelle]) VALUES (N'SAI_DGF_CP          ', N'Faire une demande Contrat Pro')
GO
INSERT [dbo].[habilitation] ([cle], [libelle]) VALUES (N'SAI_DGF_TA          ', N'Faire une demande Toutes Actions')
GO
INSERT [dbo].[habilitation] ([cle], [libelle]) VALUES (N'SUI_DGF_CP          ', N'Accéder à la liste des demandes Contrat Pro')
GO
INSERT [dbo].[habilitation] ([cle], [libelle]) VALUES (N'SUI_DGF_TA          ', N'Accéder à la liste des demandes Toutes Actions')
GO
INSERT [dbo].[habilitation] ([cle], [libelle]) VALUES (N'SUI_PAI_CP          ', N'Accéder à la liste des paiements Contrat Pro')
GO
INSERT [dbo].[habilitation] ([cle], [libelle]) VALUES (N'SUI_PAI_TA          ', N'Accéder à la liste des paiements Toutes Actions')
GO
SET IDENTITY_INSERT [dbo].[ref_beneficiaire_minimas_sociaux] ON 

GO
INSERT [dbo].[ref_beneficiaire_minimas_sociaux] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (1, N'RSA       ', N'Revenu de solidarité active', CAST(N'2015-05-13 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_beneficiaire_minimas_sociaux] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (2, N'ASS       ', N'Allocation de solidarité spécifique', CAST(N'2015-05-13 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_beneficiaire_minimas_sociaux] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (3, N'AAH       ', N'Allocation pour adulte handicapé', CAST(N'2015-05-13 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_beneficiaire_minimas_sociaux] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (4, N'API       ', N'Allocation de parent isolé', CAST(N'2015-05-13 00:00:00.000' AS DateTime), 1, CAST(N'2015-05-26 14:12:32.000' AS DateTime), 1, NULL, NULL, 0)
GO
INSERT [dbo].[ref_beneficiaire_minimas_sociaux] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (5, N'zz        ', N'ddddd', CAST(N'2015-05-26 11:10:19.000' AS DateTime), 1, NULL, NULL, CAST(N'2015-05-26 12:01:05.000' AS DateTime), 1, 1)
GO
INSERT [dbo].[ref_beneficiaire_minimas_sociaux] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (6, N'fezefz    ', N'aaaaaaaaaaaaaaaa', CAST(N'2015-05-26 11:13:48.000' AS DateTime), 1, NULL, NULL, CAST(N'2015-05-26 12:01:05.000' AS DateTime), 1, 1)
GO
INSERT [dbo].[ref_beneficiaire_minimas_sociaux] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (7, N'aa        ', N'bbbb', CAST(N'2015-05-26 12:29:30.000' AS DateTime), 1, NULL, NULL, CAST(N'2015-05-26 12:29:42.000' AS DateTime), 1, 1)
GO
INSERT [dbo].[ref_beneficiaire_minimas_sociaux] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (8, N'rze       ', N'rzqrzzzz', CAST(N'2015-05-26 14:12:44.000' AS DateTime), 1, NULL, NULL, CAST(N'2015-05-26 14:13:17.000' AS DateTime), 1, 1)
GO
INSERT [dbo].[ref_beneficiaire_minimas_sociaux] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (9, N'test      ', N'test', CAST(N'2015-05-26 14:13:25.000' AS DateTime), 1, NULL, NULL, CAST(N'2015-05-26 14:13:31.000' AS DateTime), 1, 1)
GO
SET IDENTITY_INSERT [dbo].[ref_beneficiaire_minimas_sociaux] OFF
GO
SET IDENTITY_INSERT [dbo].[ref_derniere_situation] ON 

GO
INSERT [dbo].[ref_derniere_situation] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (1, N'1         ', N'Scolaire', CAST(N'2015-05-13 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_derniere_situation] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (2, N'2         ', N'Jeune bénéficiaire du CIVIS', CAST(N'2015-05-13 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_derniere_situation] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (3, N'3         ', N'Etudiant', CAST(N'2015-05-13 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_derniere_situation] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (4, N'4         ', N'Contrat d''apprentissage', CAST(N'2015-05-13 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_derniere_situation] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (6, N'5         ', N'Contrat de professionnalisation', CAST(N'2015-05-13 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_derniere_situation] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (7, N'6         ', N'Salarié en contrat aidé : CUI-CIE, CUI-CAE', CAST(N'2015-05-13 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_derniere_situation] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (8, N'7         ', N'Stagiaire de la formation professionnelle', CAST(N'2015-05-13 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_derniere_situation] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (9, N'8         ', N'Salarié (y compris intérimaires et salariés à temps partiel) ', CAST(N'2015-05-13 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_derniere_situation] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (10, N'9         ', N'Personne à la recherche d’un emploi', CAST(N'2015-05-13 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_derniere_situation] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (11, N'10        ', N'Inactif', CAST(N'2015-05-13 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_derniere_situation] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (12, N'          ', N'', CAST(N'2015-05-26 11:55:04.000' AS DateTime), 1, NULL, NULL, CAST(N'2015-05-26 14:12:17.000' AS DateTime), 1, 1)
GO
SET IDENTITY_INSERT [dbo].[ref_derniere_situation] OFF
GO
SET IDENTITY_INSERT [dbo].[ref_diplome] ON 

GO
INSERT [dbo].[ref_diplome] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (1, N'10        ', N'Doctorat', CAST(N'2015-05-13 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_diplome] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (2, N'11        ', N'Master 2 professionnel /DESS/ diplôme grande école', CAST(N'2015-05-13 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_diplome] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (3, N'12        ', N'Master 2 recherche / DEA', CAST(N'2015-05-13 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_diplome] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (4, N'19        ', N'Autre diplôme ou titre de niveau bac +5 ou plus', CAST(N'2015-05-13 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_diplome] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (5, N'21        ', N'Master 1 professionnel ', CAST(N'2015-05-13 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_diplome] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (6, N'22        ', N'Master 1 général', CAST(N'2015-05-13 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_diplome] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (7, N'23        ', N'Licence professionnelle', CAST(N'2015-05-13 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_diplome] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (8, N'24        ', N'Licence générale 
', CAST(N'2015-05-13 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_diplome] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (9, N'29        ', N'Autre diplôme ou titre de niveau bac +3 ou 4', CAST(N'2015-05-13 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_diplome] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (10, N'31        ', N'Brevet de Technicien Supérieur', CAST(N'2015-05-13 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_diplome] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (11, N'32        ', N'Diplôme Universitaire de technologie ', CAST(N'2015-05-13 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_diplome] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (12, N'39        ', N'Autre diplôme ou titre de niveau bac +2 
', CAST(N'2015-05-13 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_diplome] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (13, N'41        ', N'Baccalauréat professionnel 
', CAST(N'2015-05-13 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_diplome] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (14, N'42        ', N'Baccalauréat général ', CAST(N'2015-05-13 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_diplome] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (15, N'43        ', N'Baccalauréat technologique ', CAST(N'2015-05-13 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_diplome] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (16, N'49        ', N'Autre diplôme ou titre de niveau bac', CAST(N'2015-05-13 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_diplome] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (17, N'51        ', N'CAP', CAST(N'2015-05-13 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_diplome] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (18, N'52        ', N'BEP
', CAST(N'2015-05-13 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_diplome] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (19, N'53        ', N'Mention complémentaire
', CAST(N'2015-05-13 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_diplome] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (20, N'59        ', N'Autre diplôme ou titre de niveau CAP/BEP', CAST(N'2015-05-13 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_diplome] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (21, N'60        ', N'Aucun diplôme ni titre professionnel', CAST(N'2015-05-13 00:00:00.000' AS DateTime), 1, CAST(N'2015-05-26 18:37:35.000' AS DateTime), 1, NULL, NULL, 0)
GO
INSERT [dbo].[ref_diplome] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (22, NULL, N'yry', CAST(N'2015-05-26 10:19:29.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_diplome] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (23, N'test      ', N'abbb', CAST(N'2015-05-26 18:33:53.000' AS DateTime), 1, CAST(N'2015-05-26 18:34:00.000' AS DateTime), 1, CAST(N'2015-05-26 18:34:33.000' AS DateTime), 1, 1)
GO
INSERT [dbo].[ref_diplome] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (24, N'nfg       ', N'fezfezbnfg', CAST(N'2015-05-26 18:35:02.000' AS DateTime), 1, CAST(N'2015-05-26 18:35:24.000' AS DateTime), 1, NULL, NULL, 0)
GO
SET IDENTITY_INSERT [dbo].[ref_diplome] OFF
GO
SET IDENTITY_INSERT [dbo].[ref_finalite_formation] ON 

GO
INSERT [dbo].[ref_finalite_formation] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (1, N'2         ', N'Certificat de qualification professionnelle (CQP)', CAST(N'2015-05-17 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_finalite_formation] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (2, N'1         ', N'Certification enregistrée au RNCP', CAST(N'2015-05-17 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_finalite_formation] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (3, N'3         ', N'Qualification reconnue dans les classifications d’une convention collective nationale', CAST(N'2015-05-17 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
SET IDENTITY_INSERT [dbo].[ref_finalite_formation] OFF
GO
SET IDENTITY_INSERT [dbo].[ref_groupe] ON 

GO
INSERT [dbo].[ref_groupe] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (1, N'GR1       ', N'GR1', CAST(N'2015-05-15 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_groupe] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (2, N'GR2       ', N'GR2', CAST(N'2015-05-15 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_groupe] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (3, N'GR3       ', N'GR3', CAST(N'2015-05-15 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 1)
GO
INSERT [dbo].[ref_groupe] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (4, N'GR4       ', N'GR4', CAST(N'2015-05-15 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
SET IDENTITY_INSERT [dbo].[ref_groupe] OFF
GO
SET IDENTITY_INSERT [dbo].[ref_justificatif] ON 

GO
INSERT [dbo].[ref_justificatif] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete], [id_ref_nature_demande], [is_mandatory]) VALUES (1, N'RM1       ', N'Convention de formation', CAST(N'2015-05-21 16:22:36.620' AS DateTime), 1, NULL, NULL, NULL, NULL, 0, 1, 1)
GO
INSERT [dbo].[ref_justificatif] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete], [id_ref_nature_demande], [is_mandatory]) VALUES (2, N'RM2       ', N'Programme', CAST(N'2015-05-21 16:22:42.497' AS DateTime), 1, CAST(N'2015-05-26 16:15:08.000' AS DateTime), 1, NULL, NULL, 0, 1, 1)
GO
INSERT [dbo].[ref_justificatif] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete], [id_ref_nature_demande], [is_mandatory]) VALUES (3, N'RM3       ', N'Cerfa signé', CAST(N'2015-05-21 16:22:49.193' AS DateTime), 1, NULL, NULL, NULL, NULL, 0, 1, 1)
GO
INSERT [dbo].[ref_justificatif] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete], [id_ref_nature_demande], [is_mandatory]) VALUES (4, N'RC1       ', N'Attestation pôle emploi si demande d''emploi de + de 26 ans', CAST(N'2015-05-21 16:22:54.323' AS DateTime), 1, NULL, NULL, NULL, NULL, 0, 1, 0)
GO
INSERT [dbo].[ref_justificatif] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete], [id_ref_nature_demande], [is_mandatory]) VALUES (5, N'RC2       ', N'Pièce justifiant de l’évaluation pré-formative', CAST(N'2015-05-21 16:22:59.863' AS DateTime), 1, NULL, NULL, NULL, NULL, 0, 1, 0)
GO
INSERT [dbo].[ref_justificatif] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete], [id_ref_nature_demande], [is_mandatory]) VALUES (6, N'RC3       ', N'Attestation MDPH SI Travailleur Handicapé', CAST(N'2015-05-21 16:23:05.670' AS DateTime), 1, NULL, NULL, NULL, NULL, 0, 1, 0)
GO
INSERT [dbo].[ref_justificatif] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete], [id_ref_nature_demande], [is_mandatory]) VALUES (7, N'RC4       ', N'Courrier CQPM', CAST(N'2015-05-21 16:23:13.197' AS DateTime), 1, NULL, NULL, NULL, NULL, 0, 1, 0)
GO
INSERT [dbo].[ref_justificatif] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete], [id_ref_nature_demande], [is_mandatory]) VALUES (8, N'RC5       ', N'Résultat du précédent examen', CAST(N'2015-05-21 16:23:13.197' AS DateTime), 1, NULL, NULL, NULL, NULL, 0, 1, 0)
GO
INSERT [dbo].[ref_justificatif] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete], [id_ref_nature_demande], [is_mandatory]) VALUES (10, N'1234567890', N'aaa', CAST(N'2015-05-26 16:20:53.000' AS DateTime), 1, CAST(N'2015-05-26 18:40:30.000' AS DateTime), 1, NULL, NULL, 0, 2, 0)
GO
INSERT [dbo].[ref_justificatif] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete], [id_ref_nature_demande], [is_mandatory]) VALUES (11, N'test      ', N'aaa', CAST(N'2015-05-26 17:20:20.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0, 4, 1)
GO
INSERT [dbo].[ref_justificatif] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete], [id_ref_nature_demande], [is_mandatory]) VALUES (12, N'a         ', N'fezfe', CAST(N'2015-05-26 17:20:32.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0, 4, 0)
GO
INSERT [dbo].[ref_justificatif] ([id], [code], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete], [id_ref_nature_demande], [is_mandatory]) VALUES (13, N'gre       ', N'gregre', CAST(N'2015-05-26 17:20:46.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0, 6, 0)
GO
SET IDENTITY_INSERT [dbo].[ref_justificatif] OFF
GO
SET IDENTITY_INSERT [dbo].[ref_nature_demande] ON 

GO
INSERT [dbo].[ref_nature_demande] ([id], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (1, N'Contrat de professionnalisation', CAST(N'2015-04-11 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_nature_demande] ([id], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (2, N'Action de formation', CAST(N'2015-04-11 00:00:00.000' AS DateTime), 1, CAST(N'2015-05-26 14:27:43.000' AS DateTime), 1, NULL, NULL, 0)
GO
INSERT [dbo].[ref_nature_demande] ([id], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (3, N'Bilan de compétences', CAST(N'2015-04-11 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_nature_demande] ([id], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (4, N'VAE', CAST(N'2015-04-11 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_nature_demande] ([id], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (5, N'GPEC', CAST(N'2015-04-11 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_nature_demande] ([id], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (6, N'Jury CQPM', CAST(N'2015-04-11 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_nature_demande] ([id], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (7, N'yry', CAST(N'2015-05-26 10:19:29.000' AS DateTime), 1, NULL, NULL, CAST(N'2015-05-26 14:15:39.000' AS DateTime), 1, 1)
GO
INSERT [dbo].[ref_nature_demande] ([id], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (8, N'test', CAST(N'2015-05-26 14:27:50.000' AS DateTime), 1, NULL, NULL, CAST(N'2015-05-26 14:27:59.000' AS DateTime), 1, 1)
GO
SET IDENTITY_INSERT [dbo].[ref_nature_demande] OFF
GO
SET IDENTITY_INSERT [dbo].[ref_nature_formation] ON 

GO
INSERT [dbo].[ref_nature_formation] ([id], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (1, N'Adaptation au poste ou maintien dans l''emploi', CAST(N'2015-04-11 00:00:00.000' AS DateTime), 1, CAST(N'2015-05-26 14:35:02.000' AS DateTime), 1, NULL, NULL, 0)
GO
INSERT [dbo].[ref_nature_formation] ([id], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (2, N'Développement des compétences', CAST(N'2015-04-11 00:00:00.000' AS DateTime), 1, NULL, NULL, NULL, NULL, 0)
GO
INSERT [dbo].[ref_nature_formation] ([id], [label], [date_creation], [id_user_creation], [date_last_edit], [id_user_last_edit], [date_delete], [id_user_delete], [is_delete]) VALUES (3, N'test', CAST(N'2015-05-26 14:35:08.000' AS DateTime), 1, NULL, NULL, CAST(N'2015-05-26 14:35:14.000' AS DateTime), 1, 1)
GO
SET IDENTITY_INSERT [dbo].[ref_nature_formation] OFF
GO
ALTER TABLE [dbo].[dgf] ADD  CONSTRAINT [DF_dgf_multi_etablissement]  DEFAULT ((0)) FOR [multi_etablissement]
GO
ALTER TABLE [dbo].[dgf] ADD  CONSTRAINT [DF_dgf_is_delete]  DEFAULT ((0)) FOR [is_delete]
GO
ALTER TABLE [dbo].[dgf_form_contrat] ADD  CONSTRAINT [DF_dgf_form_contrat_is_delete_1]  DEFAULT ((0)) FOR [is_delete]
GO
ALTER TABLE [dbo].[dgf_form_demande] ADD  CONSTRAINT [DF_dgf_form_demande_is_delete]  DEFAULT ((0)) FOR [is_delete]
GO
ALTER TABLE [dbo].[dgf_form_formation] ADD  CONSTRAINT [DF_dgf_t_form_formation_formation_interne]  DEFAULT ((0)) FOR [t_formation_interne]
GO
ALTER TABLE [dbo].[dgf_form_formation] ADD  CONSTRAINT [DF_t_dgf_form_formation_formation_intra_entreprise]  DEFAULT ((0)) FOR [t_formation_intra_entreprise]
GO
ALTER TABLE [dbo].[dgf_form_formation] ADD  CONSTRAINT [DF_dgf_form_formation_is_delete_1]  DEFAULT ((0)) FOR [is_delete]
GO
ALTER TABLE [dbo].[dgf_form_formation_repartition] ADD  CONSTRAINT [DF_dgf_form_formation_repartition_is_delete]  DEFAULT ((0)) FOR [is_delete]
GO
ALTER TABLE [dbo].[dgf_form_justificatif] ADD  CONSTRAINT [DF_t_dgf_justificatif_obligatoire]  DEFAULT ((0)) FOR [t_obligatoire]
GO
ALTER TABLE [dbo].[dgf_form_justificatif] ADD  CONSTRAINT [DF_dgf_form_justificatif_is_delete_1]  DEFAULT ((0)) FOR [is_delete]
GO
ALTER TABLE [dbo].[dgf_form_justificatif_paiement] ADD  CONSTRAINT [DF_dgf_form_justificatif_paiement_t_obligatoire]  DEFAULT ((0)) FOR [t_obligatoire]
GO
ALTER TABLE [dbo].[dgf_form_justificatif_paiement] ADD  CONSTRAINT [DF_dgf_form_justificatif_paiement_is_delete_1]  DEFAULT ((0)) FOR [is_delete]
GO
ALTER TABLE [dbo].[dgf_form_organisme_formation] ADD  CONSTRAINT [DF_dgf_form_organisme_formation_is_delete_1]  DEFAULT ((0)) FOR [is_delete]
GO
ALTER TABLE [dbo].[dgf_form_salarie] ADD  CONSTRAINT [DF_dgf_form_salarie_mobilisation_cpf_1]  DEFAULT ((0)) FOR [t_mobilisation_cpf]
GO
ALTER TABLE [dbo].[dgf_form_salarie] ADD  CONSTRAINT [DF_dgf_form_salarie_is_delete_1]  DEFAULT ((0)) FOR [is_delete]
GO
ALTER TABLE [dbo].[dgf_form_tuteur] ADD  CONSTRAINT [DF_t_dgf_form_tuteur_formation_tuteur]  DEFAULT ((0)) FOR [t_formation_tuteur]
GO
ALTER TABLE [dbo].[dgf_form_tuteur] ADD  CONSTRAINT [DF_t_dgf_form_tuteur_certif_role_tuteur]  DEFAULT ((0)) FOR [t_certif_role_tuteur]
GO
ALTER TABLE [dbo].[dgf_form_tuteur] ADD  CONSTRAINT [DF_t_dgf_form_tuteur_certif_deux_ans_exp]  DEFAULT ((0)) FOR [t_certif_deux_ans_exp]
GO
ALTER TABLE [dbo].[dgf_form_tuteur] ADD  CONSTRAINT [DF_dgf_form_tuteur_is_delete_1]  DEFAULT ((0)) FOR [is_delete]
GO
ALTER TABLE [dbo].[dgf_paiement] ADD  CONSTRAINT [DF_dgf_paiement_is_delete]  DEFAULT ((0)) FOR [is_delete]
GO
ALTER TABLE [dbo].[drupal_user] ADD  CONSTRAINT [DF_drupal_user_is_delete]  DEFAULT ((0)) FOR [is_delete]
GO
ALTER TABLE [dbo].[lien_dgf_ref_esclave_entreprise] ADD  CONSTRAINT [DF_lien_dgf_ref_esclave_entreprise_is_delete]  DEFAULT ((0)) FOR [is_delete]
GO
ALTER TABLE [dbo].[ref_nomenclature_fichier_reporting] ADD  CONSTRAINT [DF_ref_nomenclature_fichier_reporting_is_delete]  DEFAULT ((0)) FOR [is_delete]
GO
ALTER TABLE [dbo].[ref_params] ADD  CONSTRAINT [DF_ref_params_is_delete]  DEFAULT ((0)) FOR [is_delete]
GO
ALTER TABLE [dbo].[ref_type_contrat] ADD  CONSTRAINT [DF_ref_type_contrat_is_delete]  DEFAULT ((0)) FOR [is_delete]
GO
ALTER TABLE [dbo].[temp_dgf_form_contrat] ADD  CONSTRAINT [DF_dgf_form_contrat_is_delete]  DEFAULT ((0)) FOR [is_delete]
GO
ALTER TABLE [dbo].[temp_dgf_form_formation] ADD  CONSTRAINT [DF_dgf_form_formation_formation_interne]  DEFAULT ((0)) FOR [formation_interne]
GO
ALTER TABLE [dbo].[temp_dgf_form_formation] ADD  CONSTRAINT [DF_dgf_form_formation_formation_intra_entreprise]  DEFAULT ((0)) FOR [formation_intra_entreprise]
GO
ALTER TABLE [dbo].[temp_dgf_form_formation] ADD  CONSTRAINT [DF_dgf_form_formation_is_delete]  DEFAULT ((0)) FOR [is_delete]
GO
ALTER TABLE [dbo].[temp_dgf_form_justificatif] ADD  CONSTRAINT [DF_dgf_form_justificatif_is_delete]  DEFAULT ((0)) FOR [is_delete]
GO
ALTER TABLE [dbo].[temp_dgf_form_justificatif_paiement] ADD  CONSTRAINT [DF_dgf_form_justificatif_paiement_obligatoire]  DEFAULT ((0)) FOR [obligatoire]
GO
ALTER TABLE [dbo].[temp_dgf_form_justificatif_paiement] ADD  CONSTRAINT [DF_dgf_form_justificatif_paiement_is_delete]  DEFAULT ((0)) FOR [is_delete]
GO
ALTER TABLE [dbo].[temp_dgf_form_organisme_formation] ADD  CONSTRAINT [DF_dgf_form_organisme_formation_is_delete]  DEFAULT ((0)) FOR [is_delete]
GO
ALTER TABLE [dbo].[temp_dgf_form_salarie] ADD  CONSTRAINT [DF_dgf_form_salarie_mobilisation_cpf]  DEFAULT ((0)) FOR [mobilisation_cpf]
GO
ALTER TABLE [dbo].[temp_dgf_form_salarie] ADD  CONSTRAINT [DF_dgf_form_salarie_is_delete]  DEFAULT ((0)) FOR [is_delete]
GO
ALTER TABLE [dbo].[temp_dgf_form_tuteur] ADD  CONSTRAINT [DF_dgf_form_tuteur_formation_tuteur]  DEFAULT ((0)) FOR [formation_tuteur]
GO
ALTER TABLE [dbo].[temp_dgf_form_tuteur] ADD  CONSTRAINT [DF_dgf_form_tuteur_info_role_tuteur]  DEFAULT ((0)) FOR [certif_role_tuteur]
GO
ALTER TABLE [dbo].[temp_dgf_form_tuteur] ADD  CONSTRAINT [DF_dgf_form_tuteur_certif_deux_ans_exp]  DEFAULT ((0)) FOR [certif_deux_ans_exp]
GO
ALTER TABLE [dbo].[temp_dgf_form_tuteur] ADD  CONSTRAINT [DF_dgf_form_tuteur_is_delete]  DEFAULT ((0)) FOR [is_delete]
GO
ALTER TABLE [dbo].[user_entreprise] ADD  CONSTRAINT [DF_user_entreprise_charte_signe]  DEFAULT ((0)) FOR [charte_signe]
GO
ALTER TABLE [dbo].[user_organisme_formation] ADD  CONSTRAINT [DF_user_organisme_formation_charte_signe]  DEFAULT ((0)) FOR [charte_signe]
GO
ALTER TABLE [dbo].[dgf_form_contrat]  WITH CHECK ADD  CONSTRAINT [FK_dgf_form_contrat_dgf] FOREIGN KEY([id_dgf])
REFERENCES [dbo].[dgf] ([id])
GO
ALTER TABLE [dbo].[dgf_form_contrat] CHECK CONSTRAINT [FK_dgf_form_contrat_dgf]
GO
ALTER TABLE [dbo].[dgf_form_demande]  WITH CHECK ADD  CONSTRAINT [FK_dgf_form_demande_dgf] FOREIGN KEY([id_dgf])
REFERENCES [dbo].[dgf] ([id])
GO
ALTER TABLE [dbo].[dgf_form_demande] CHECK CONSTRAINT [FK_dgf_form_demande_dgf]
GO
ALTER TABLE [dbo].[dgf_form_formation]  WITH CHECK ADD  CONSTRAINT [FK_dgf_form_formation_dgf] FOREIGN KEY([id_dgf])
REFERENCES [dbo].[dgf] ([id])
GO
ALTER TABLE [dbo].[dgf_form_formation] CHECK CONSTRAINT [FK_dgf_form_formation_dgf]
GO
ALTER TABLE [dbo].[dgf_form_formation_repartition]  WITH CHECK ADD  CONSTRAINT [FK_dgf_form_formation_repartition_dgf_form_formation1] FOREIGN KEY([id_dgf_form_formation])
REFERENCES [dbo].[dgf_form_formation] ([id])
GO
ALTER TABLE [dbo].[dgf_form_formation_repartition] CHECK CONSTRAINT [FK_dgf_form_formation_repartition_dgf_form_formation1]
GO
ALTER TABLE [dbo].[dgf_form_justificatif]  WITH CHECK ADD  CONSTRAINT [FK_dgf_form_justificatif_dgf] FOREIGN KEY([id_dgf])
REFERENCES [dbo].[dgf] ([id])
GO
ALTER TABLE [dbo].[dgf_form_justificatif] CHECK CONSTRAINT [FK_dgf_form_justificatif_dgf]
GO
ALTER TABLE [dbo].[dgf_form_justificatif_paiement]  WITH CHECK ADD  CONSTRAINT [FK_dgf_form_justificatif_paiement_dgf] FOREIGN KEY([id_dgf])
REFERENCES [dbo].[dgf] ([id])
GO
ALTER TABLE [dbo].[dgf_form_justificatif_paiement] CHECK CONSTRAINT [FK_dgf_form_justificatif_paiement_dgf]
GO
ALTER TABLE [dbo].[dgf_form_organisme_formation]  WITH CHECK ADD  CONSTRAINT [FK_dgf_form_organisme_formation_dgf] FOREIGN KEY([id_dgf])
REFERENCES [dbo].[dgf] ([id])
GO
ALTER TABLE [dbo].[dgf_form_organisme_formation] CHECK CONSTRAINT [FK_dgf_form_organisme_formation_dgf]
GO
ALTER TABLE [dbo].[dgf_form_salarie]  WITH CHECK ADD  CONSTRAINT [FK_dgf_form_salarie_dgf] FOREIGN KEY([id_dgf])
REFERENCES [dbo].[dgf] ([id])
GO
ALTER TABLE [dbo].[dgf_form_salarie] CHECK CONSTRAINT [FK_dgf_form_salarie_dgf]
GO
ALTER TABLE [dbo].[dgf_form_tuteur]  WITH CHECK ADD  CONSTRAINT [FK_dgf_form_tuteur_dgf] FOREIGN KEY([id_dgf])
REFERENCES [dbo].[dgf] ([id])
GO
ALTER TABLE [dbo].[dgf_form_tuteur] CHECK CONSTRAINT [FK_dgf_form_tuteur_dgf]
GO
ALTER TABLE [dbo].[dgf_paiement]  WITH CHECK ADD  CONSTRAINT [FK_dgf_paiement_dgf] FOREIGN KEY([id_dgf])
REFERENCES [dbo].[dgf] ([id])
GO
ALTER TABLE [dbo].[dgf_paiement] CHECK CONSTRAINT [FK_dgf_paiement_dgf]
GO
ALTER TABLE [dbo].[lien_dgf_ref_esclave_entreprise]  WITH CHECK ADD  CONSTRAINT [FK_lien_dgf_ref_esclave_entreprise_dgf] FOREIGN KEY([id_dgf])
REFERENCES [dbo].[dgf] ([id])
GO
ALTER TABLE [dbo].[lien_dgf_ref_esclave_entreprise] CHECK CONSTRAINT [FK_lien_dgf_ref_esclave_entreprise_dgf]
GO
ALTER TABLE [dbo].[lien_drupal_user_habilitation]  WITH CHECK ADD  CONSTRAINT [FK_lien_drupal_user_habilitation_drupal_user] FOREIGN KEY([id_drupal_user])
REFERENCES [dbo].[drupal_user] ([id])
GO
ALTER TABLE [dbo].[lien_drupal_user_habilitation] CHECK CONSTRAINT [FK_lien_drupal_user_habilitation_drupal_user]
GO
ALTER TABLE [dbo].[lien_drupal_user_habilitation]  WITH CHECK ADD  CONSTRAINT [FK_lien_drupal_user_habilitation_habilitation] FOREIGN KEY([id_habilitation])
REFERENCES [dbo].[habilitation] ([cle])
GO
ALTER TABLE [dbo].[lien_drupal_user_habilitation] CHECK CONSTRAINT [FK_lien_drupal_user_habilitation_habilitation]
GO
ALTER TABLE [dbo].[lien_ref_finalite_formation_nature_demande]  WITH CHECK ADD  CONSTRAINT [FK_lien_ref_finalite_formation_nature_demande_ref_finalite_formation] FOREIGN KEY([id_ref_finalite_formation])
REFERENCES [dbo].[ref_finalite_formation] ([id])
GO
ALTER TABLE [dbo].[lien_ref_finalite_formation_nature_demande] CHECK CONSTRAINT [FK_lien_ref_finalite_formation_nature_demande_ref_finalite_formation]
GO
ALTER TABLE [dbo].[lien_ref_finalite_formation_nature_demande]  WITH CHECK ADD  CONSTRAINT [FK_lien_ref_finalite_formation_nature_demande_ref_nature_demande] FOREIGN KEY([id_ref_nature_demande])
REFERENCES [dbo].[ref_nature_demande] ([id])
GO
ALTER TABLE [dbo].[lien_ref_finalite_formation_nature_demande] CHECK CONSTRAINT [FK_lien_ref_finalite_formation_nature_demande_ref_nature_demande]
GO
ALTER TABLE [dbo].[lien_ref_nature_demande_ref_justificatif]  WITH CHECK ADD  CONSTRAINT [FK_lien_ref_nature_demande_ref_justificatif_ref_justificatif] FOREIGN KEY([id_ref_justificatif])
REFERENCES [dbo].[ref_justificatif] ([id])
GO
ALTER TABLE [dbo].[lien_ref_nature_demande_ref_justificatif] CHECK CONSTRAINT [FK_lien_ref_nature_demande_ref_justificatif_ref_justificatif]
GO
ALTER TABLE [dbo].[lien_ref_nature_demande_ref_justificatif]  WITH CHECK ADD  CONSTRAINT [FK_lien_ref_nature_demande_ref_justificatif_ref_nature_demande] FOREIGN KEY([id_ref_nature_demande])
REFERENCES [dbo].[ref_nature_demande] ([id])
GO
ALTER TABLE [dbo].[lien_ref_nature_demande_ref_justificatif] CHECK CONSTRAINT [FK_lien_ref_nature_demande_ref_justificatif_ref_nature_demande]
GO
ALTER TABLE [dbo].[lien_ref_nature_demande_ref_nature_formation]  WITH CHECK ADD  CONSTRAINT [FK_lien_ref_nature_demande_ref_nature_formation_ref_nature_demande] FOREIGN KEY([id_ref_nature_demande])
REFERENCES [dbo].[ref_nature_demande] ([id])
GO
ALTER TABLE [dbo].[lien_ref_nature_demande_ref_nature_formation] CHECK CONSTRAINT [FK_lien_ref_nature_demande_ref_nature_formation_ref_nature_demande]
GO
ALTER TABLE [dbo].[lien_ref_nature_demande_ref_nature_formation]  WITH CHECK ADD  CONSTRAINT [FK_lien_ref_nature_demande_ref_nature_formation_ref_nature_formation] FOREIGN KEY([id_ref_nature_formation])
REFERENCES [dbo].[ref_nature_formation] ([id])
GO
ALTER TABLE [dbo].[lien_ref_nature_demande_ref_nature_formation] CHECK CONSTRAINT [FK_lien_ref_nature_demande_ref_nature_formation_ref_nature_formation]
GO
ALTER TABLE [dbo].[lien_user_autre_entreprise]  WITH CHECK ADD  CONSTRAINT [FK_lien_user_autre_entreprise_user_autre] FOREIGN KEY([id_user_autre])
REFERENCES [dbo].[user_autre] ([id])
GO
ALTER TABLE [dbo].[lien_user_autre_entreprise] CHECK CONSTRAINT [FK_lien_user_autre_entreprise_user_autre]
GO
ALTER TABLE [dbo].[lien_user_entreprise_ref_esclave_entreprise]  WITH CHECK ADD  CONSTRAINT [FK_lien_user_entreprise_ref_esclave_entreprise_user_entreprise] FOREIGN KEY([id_user_entreprise])
REFERENCES [dbo].[user_entreprise] ([id])
GO
ALTER TABLE [dbo].[lien_user_entreprise_ref_esclave_entreprise] CHECK CONSTRAINT [FK_lien_user_entreprise_ref_esclave_entreprise_user_entreprise]
GO
ALTER TABLE [dbo].[temp_dgf_form_contrat]  WITH CHECK ADD  CONSTRAINT [FK_dgf_form_contrat_ref_groupe] FOREIGN KEY([id_ref_groupe])
REFERENCES [dbo].[ref_groupe] ([id])
GO
ALTER TABLE [dbo].[temp_dgf_form_contrat] CHECK CONSTRAINT [FK_dgf_form_contrat_ref_groupe]
GO
ALTER TABLE [dbo].[temp_dgf_form_contrat]  WITH CHECK ADD  CONSTRAINT [FK_temp_dgf_form_contrat_dgf] FOREIGN KEY([id_dgf])
REFERENCES [dbo].[dgf] ([id])
GO
ALTER TABLE [dbo].[temp_dgf_form_contrat] CHECK CONSTRAINT [FK_temp_dgf_form_contrat_dgf]
GO
ALTER TABLE [dbo].[temp_dgf_form_demande]  WITH CHECK ADD  CONSTRAINT [FK_temp_dgf_form_demande_dgf] FOREIGN KEY([id_dgf])
REFERENCES [dbo].[dgf] ([id])
GO
ALTER TABLE [dbo].[temp_dgf_form_demande] CHECK CONSTRAINT [FK_temp_dgf_form_demande_dgf]
GO
ALTER TABLE [dbo].[temp_dgf_form_formation]  WITH CHECK ADD  CONSTRAINT [FK_temp_dgf_form_formation_dgf] FOREIGN KEY([id_dgf])
REFERENCES [dbo].[dgf] ([id])
GO
ALTER TABLE [dbo].[temp_dgf_form_formation] CHECK CONSTRAINT [FK_temp_dgf_form_formation_dgf]
GO
ALTER TABLE [dbo].[temp_dgf_form_formation_repartition]  WITH CHECK ADD  CONSTRAINT [FK_dgf_form_formation_repartition_dgf_form_formation] FOREIGN KEY([id_dgf_form_formation])
REFERENCES [dbo].[temp_dgf_form_formation] ([id])
GO
ALTER TABLE [dbo].[temp_dgf_form_formation_repartition] CHECK CONSTRAINT [FK_dgf_form_formation_repartition_dgf_form_formation]
GO
ALTER TABLE [dbo].[temp_dgf_form_justificatif]  WITH CHECK ADD  CONSTRAINT [FK_dgf_form_justificatif_ref_justificatif] FOREIGN KEY([id_ref_justificatifs])
REFERENCES [dbo].[ref_justificatif] ([id])
GO
ALTER TABLE [dbo].[temp_dgf_form_justificatif] CHECK CONSTRAINT [FK_dgf_form_justificatif_ref_justificatif]
GO
ALTER TABLE [dbo].[temp_dgf_form_justificatif]  WITH CHECK ADD  CONSTRAINT [FK_temp_dgf_form_justificatif_dgf] FOREIGN KEY([id_dgf])
REFERENCES [dbo].[dgf] ([id])
GO
ALTER TABLE [dbo].[temp_dgf_form_justificatif] CHECK CONSTRAINT [FK_temp_dgf_form_justificatif_dgf]
GO
ALTER TABLE [dbo].[temp_dgf_form_justificatif_paiement]  WITH CHECK ADD  CONSTRAINT [FK_temp_dgf_form_justificatif_paiement_dgf] FOREIGN KEY([id_dgf])
REFERENCES [dbo].[dgf] ([id])
GO
ALTER TABLE [dbo].[temp_dgf_form_justificatif_paiement] CHECK CONSTRAINT [FK_temp_dgf_form_justificatif_paiement_dgf]
GO
ALTER TABLE [dbo].[temp_dgf_form_organisme_formation]  WITH CHECK ADD  CONSTRAINT [FK_temp_dgf_form_organisme_formation_dgf] FOREIGN KEY([id_dgf])
REFERENCES [dbo].[dgf] ([id])
GO
ALTER TABLE [dbo].[temp_dgf_form_organisme_formation] CHECK CONSTRAINT [FK_temp_dgf_form_organisme_formation_dgf]
GO
ALTER TABLE [dbo].[temp_dgf_form_salarie]  WITH CHECK ADD  CONSTRAINT [FK_temp_dgf_form_salarie_dgf] FOREIGN KEY([id_dgf])
REFERENCES [dbo].[dgf] ([id])
GO
ALTER TABLE [dbo].[temp_dgf_form_salarie] CHECK CONSTRAINT [FK_temp_dgf_form_salarie_dgf]
GO
ALTER TABLE [dbo].[temp_dgf_form_salarie]  WITH CHECK ADD  CONSTRAINT [FK_temp_dgf_form_salarie_ref_beneficiaire_minimas_sociaux] FOREIGN KEY([id_ref_beneficiaire_minimas_sociaux])
REFERENCES [dbo].[ref_beneficiaire_minimas_sociaux] ([id])
GO
ALTER TABLE [dbo].[temp_dgf_form_salarie] CHECK CONSTRAINT [FK_temp_dgf_form_salarie_ref_beneficiaire_minimas_sociaux]
GO
ALTER TABLE [dbo].[temp_dgf_form_salarie]  WITH CHECK ADD  CONSTRAINT [FK_temp_dgf_form_salarie_ref_derniere_situation] FOREIGN KEY([id_ref_derniere_situation])
REFERENCES [dbo].[ref_derniere_situation] ([id])
GO
ALTER TABLE [dbo].[temp_dgf_form_salarie] CHECK CONSTRAINT [FK_temp_dgf_form_salarie_ref_derniere_situation]
GO
ALTER TABLE [dbo].[temp_dgf_form_salarie]  WITH CHECK ADD  CONSTRAINT [FK_temp_dgf_form_salarie_ref_diplome] FOREIGN KEY([id_ref_diplome])
REFERENCES [dbo].[ref_diplome] ([id])
GO
ALTER TABLE [dbo].[temp_dgf_form_salarie] CHECK CONSTRAINT [FK_temp_dgf_form_salarie_ref_diplome]
GO
ALTER TABLE [dbo].[temp_dgf_form_tuteur]  WITH CHECK ADD  CONSTRAINT [FK_temp_dgf_form_tuteur_dgf] FOREIGN KEY([id_dgf])
REFERENCES [dbo].[dgf] ([id])
GO
ALTER TABLE [dbo].[temp_dgf_form_tuteur] CHECK CONSTRAINT [FK_temp_dgf_form_tuteur_dgf]
GO
ALTER TABLE [dbo].[temp_dgf_form_tuteur]  WITH CHECK ADD  CONSTRAINT [FK_temp_dgf_form_tuteur_ref_diplome] FOREIGN KEY([id_ref_diplome])
REFERENCES [dbo].[ref_diplome] ([id])
GO
ALTER TABLE [dbo].[temp_dgf_form_tuteur] CHECK CONSTRAINT [FK_temp_dgf_form_tuteur_ref_diplome]
GO
ALTER TABLE [dbo].[user_autre]  WITH CHECK ADD  CONSTRAINT [FK_user_autre_drupal_user] FOREIGN KEY([id_drupal_user])
REFERENCES [dbo].[drupal_user] ([id])
GO
ALTER TABLE [dbo].[user_autre] CHECK CONSTRAINT [FK_user_autre_drupal_user]
GO
ALTER TABLE [dbo].[user_entreprise]  WITH CHECK ADD  CONSTRAINT [FK_user_entreprise_drupal_user] FOREIGN KEY([id_drupal_user])
REFERENCES [dbo].[drupal_user] ([id])
GO
ALTER TABLE [dbo].[user_entreprise] CHECK CONSTRAINT [FK_user_entreprise_drupal_user]
GO
ALTER TABLE [dbo].[user_entreprise]  WITH CHECK ADD  CONSTRAINT [FK_user_entreprise_user_responsable] FOREIGN KEY([id_user_responsable])
REFERENCES [dbo].[user_responsable] ([id])
GO
ALTER TABLE [dbo].[user_entreprise] CHECK CONSTRAINT [FK_user_entreprise_user_responsable]
GO
ALTER TABLE [dbo].[user_organisme_formation]  WITH CHECK ADD  CONSTRAINT [FK_user_organisme_formation_drupal_user] FOREIGN KEY([id_drupal_user])
REFERENCES [dbo].[drupal_user] ([id])
GO
ALTER TABLE [dbo].[user_organisme_formation] CHECK CONSTRAINT [FK_user_organisme_formation_drupal_user]
GO
ALTER TABLE [dbo].[user_organisme_formation]  WITH CHECK ADD  CONSTRAINT [FK_user_organisme_formation_user_responsable] FOREIGN KEY([id_user_responsable])
REFERENCES [dbo].[user_responsable] ([id])
GO
ALTER TABLE [dbo].[user_organisme_formation] CHECK CONSTRAINT [FK_user_organisme_formation_user_responsable]
GO
SET DATEFORMAT DMY