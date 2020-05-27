#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "fournisseur.h"
#include <QMainWindow>
#include "nourriture.h"
#include<QElapsedTimer>
#include <QMediaPlayer>
#include <QStandardItemModel>
#include <QMediaPlaylist>
#include <QTime>
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>
#include<QBarSet>
#include<QBarSeries>
#include <QtCharts/QCategoryAxis>
#include "../SMTPClient/email.h"
#include "../SMTPClient/smtpclient.h"
#include "../SMTPClient/emailaddress.h"
#include <QtCharts/QChartView>
#include "avis_fournisseur.h"
#include <QTranslator>
#include <QtPlugin>
#include"profil.h"
#include "login.h"
#include"ouvrier.h"
#include "plante.h"
#include "produitv.h"
#include "equipement.h"
#include "vehicule.h"
#include "produit.h"
#include "animal.h"
//Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class QSystemTrayIcon;
class QPrinter;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool test;

public slots :
    void time();
    void chat();
private slots:

    void on_pushButton_nour_four_clicked();

    void on_pushButton_admin_clicked();

    void on_pushButton_plante_clicked();

    void on_pushButton_materiel_clicked();

    void on_pushButton_animal_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_ajoutern_clicked();

    void on_pushButton_triendesc_clicked();

    void on_pushButton_ajf_clicked();



    void on_pushButton_ajouterf_clicked();

    void on_tabfournisseur_activated(const QModelIndex &index);

    void on_fs_clicked();

    void on_fm_clicked();

    void on_pushButton_ajn_clicked();

    void on_tabnourriture_activated(const QModelIndex &index);

    void on_nm_clicked();

    void on_ns_clicked();

    void on_tabWidget_baha_currentChanged();

    void on_tabWidget_baha_currentChanged(int index);

    void on_pushButton_ajn_2_clicked();

    void on_pushButton_trienasc_clicked();

    void on_pushButton_triefdesc_clicked();

    void on_rech_n_clicked();

    void on_lineEdit_telf_cursorPositionChanged();

    void on_lineEdit_nomf_cursorPositionChanged();

    void on_lineEdit_adressef_cursorPositionChanged();

    void on_lineEdit_idf_cursorPositionChanged();

    void on_lineEdit_nomn_cursorPositionChanged();

    void on_lineEdit_emailf_cursorPositionChanged();

    void on_pushButton_mailn_clicked();

    void on_pushButton_triefasc_clicked();

    //void on_sliderv_actionTriggered(int action);

    void on_sliderp_sliderMoved(int position);
    void on_position_Changed(int position);
    void on_duration_Changed(int position);

   // void on_sliderv_rangeChanged(int min, int max);

    void on_sliderv_sliderMoved(int position);
    void on_actionCheck_database_triggered();
   // void on_actionsettings_triggered();
    void on_action_settings_triggered();

    void on_pushButton_statn_clicked();

    void on_pushButton_6_clicked();

    void on_btn_add_clicked();

    //void on_label_25_linkActivated(const QString &link);

//    void on_comboBox_activated(const QString &arg1);

  //  void on_pushButton_10_clicked();

    void on_comboBox_bgapp_currentIndexChanged(const QString &arg1);

    void on_comboBox_4_currentIndexChanged(const QString &arg1);

    void on_recherche_textChanged(const QString &arg1);

    void on_returnmn_clicked();

    void sendEmail();
    void sendEmail_2();
    void sendEmail_3();

    void clearFields();

    void onStatus(Status::e status, QString errorMessage);

    //void on_pushButtonClear_clicked();

    //void on_btn_add_triggered(QAction *arg1);

    void on_btn_add_2_clicked();

    void on_pushButton_mailf_clicked();

    void on_pushButton_statf_clicked();

    void on_pushButton_9_clicked();

    void on_returnmn_2_clicked();

    void on_pushButton_rechf_clicked();

    void on_pushButton_ajf_2_clicked();

    void on_recherche_f_textChanged(const QString &arg1);

    void on_boutton_avis_clicked();

    void on_returnmn_3_clicked();

    void on_pushButton_ajn_4_clicked();

    //void on_pushButton_ajn_5_clicked();

    void on_pushButton_ajout_avis_clicked();

   // void on_pushButton_aja_clicked();

    void on_pushButton_rfa_clicked();

    void on_pushButton_ajaf_clicked();

    void on_tabavisf_activated(const QModelIndex &index);

    void on_am_clicked();

    void on_as_clicked();

    void on_btn_add_3_clicked();

    void on_print_nour_clicked();

    void on_print_four_clicked();
    void print(QPrinter *);
    void print2(QPrinter *);

    void on_cutf_clicked();

    void on_pastf_clicked();

    void on_copyf_clicked();

    void on_gobf_clicked();

    void on_goff_clicked();

    void on_newf_clicked();

    void on_openf_clicked();

    void on_savef_clicked();

    void on_saveasf_clicked();

    void on_printt_clicked();

    void on_returnmn_4_clicked();

    void on_boutton_note_clicked();

    void on_fontt_clicked();

    void on_colort_clicked();

    void on_bgcolort_clicked();

    void on_bgct_clicked();

    void on_boutton_note_2_clicked();

    void on_returnmn_5_clicked();

    void on_newf_2_clicked();

    void on_openf_2_clicked();

    void on_savef_2_clicked();

    void on_saveasf_2_clicked();

    void on_cutf_2_clicked();

    void on_copyf_2_clicked();

    void on_pastf_2_clicked();

    void on_gobf_2_clicked();

    void on_goff_2_clicked();

    void on_printt_2_clicked();

    void on_fontt_2_clicked();

    void on_colort_2_clicked();

    void on_bgcolort_2_clicked();

    void on_bgct_2_clicked();

    void on_export_coln_clicked();

    void on_export_colf_clicked();

    //void on_comboBox_bgapp_activated(const QString &arg1);

    void on_boutton_French_clicked();

    void on_boutton_English_clicked();

  //  void on_pushButtonSend_clicked();

  //  void on_btn_add_3_triggered(QAction *arg1);

  //  void on_pushButtonSend_2_clicked();

 //   void on_bttn_muter_clicked();

 //   void on_comboBox_bgapp_currentTextChanged(const QString &arg1);

    void on_bttn_muter_linkActivated(const QString &link);

    void on_pushButton_14_clicked();

    void on_login_btn_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_triedown_ouvrier_clicked();

    void on_recherche_ouvrier_clicked();
    void on_trieup_ouvrier_clicked();
    void on_recherche_profile_clicked();

    void on_trieup_profile_clicked();

    void on_triedown_profile_clicked();
   // void on_ajouter_profile_clicked();

    void on_ajouter_profile_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_37_clicked();

    void on_pushButton_38_clicked();

    void on_pushButton_55_clicked();

    void on_pushButton_56_clicked();

    void on_supprimer_profile_clicked();

    void on_modifier_profile_clicked();

    void on_pushButton_50_clicked();

    void on_pushButton_60_clicked();

    void on_pushButton_59_clicked();

    void on_ajouter_ouvrier_clicked();

    void on_supprimer_ouvrier_clicked();

    void on_modifier_ouvrier_clicked();

    void on_pushButton_49_clicked();

    void on_supprimer_ouv_2_clicked();

    void on_pushButton_58_clicked();

    void on_pushButton_53_clicked();

    void on_pushButton_54_clicked();

    void on_pushButton_61_clicked();

    void on_stats_clicked();

    void on_ajouterplante_clicked();

    void on_anulerajouterplante_clicked();

    void on_ajoutplante_clicked();

    void on_afficherplantes_activated(const QModelIndex &index);

    void on_mod_clicked();

    void on_anulersupprimerplante_clicked();

    void on_supprimerplante_2_clicked();

    void on_supprimerplante_clicked();

    void on_validrechercheplante_clicked();

    void on_nomrecherche_textChanged(const QString &arg1);

    void on_pushButton_20_clicked();

    void on_pushButton_19_clicked();

    void on_annulersupprimerproduitv_clicked();

    void on_annulerajouterproduitv_clicked();

    void on_ajouterproduitv_clicked();

    void on_supprimerproduitv_clicked();

    void on_tabWidget_3_currentChanged(int index);

    void on_afficherproduitv_activated(const QModelIndex &index);

    void on_mod_2_clicked();

    void on_ajouterproduitv_2_clicked();

    void on_supprimerproduitv_2_clicked();

    void on_produitvdown_clicked();

    void on_produitvup_clicked();

    void on_rechercherproduitv_clicked();

    void on_pushButton_57_clicked();

    void on_pushButton_62_clicked();

   // void on_pushButton_63_clicked();

    void on_ajouter_vehicule_clicked();

    void on_modifier_vehicule_clicked();

    void on_supprimer_vehicule_clicked();

    void on_retour_vehicule_a_clicked();

    void on_retour_vehicule_m_clicked();

    void on_retour_vehicule_s_clicked();

    void on_button_ajouter_vehicule_clicked();

    void on_Modifier_vehicule_clicked();

    void on_supp_vehicule_clicked();

    void on_tabWidget_5_currentChanged(int index);

    void on_chercher_vehicule_clicked();

    void on_tri_asc_vehilcule_clicked();

    void on_tri_desc_vehilcule_clicked();

    void on_retour_equipement_2_clicked();

    void on_retour_equi_clicked();

    void on_pushButton_21_clicked();

    void on_page_ajouter_equipement_clicked();

    void on_modifier_equipement_clicked();

    void on_supprimer_equipement_clicked();

    void on_supp_equipement_clicked();

    void on_update_equipement_clicked();

    void on_ajouter_equipement_clicked();

    void on_chercher_equipement_clicked();

    void on_tri_asc_equipement_clicked();

    void on_tri_desc_equipement_clicked();

    void on_pushButton_63_clicked();

    void on_pushButton_64_clicked();

    //void on_lineEdit_idf_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_refn_textChanged(const QString &arg1);

    void on_pushButton_stat_plante_clicked();

    void on_pushButton_retourstatp_clicked();

    void on_pushButton_retourstatp_2_clicked();

    void on_pushButton_stat_plante_2_clicked();

    void on_boutton_settings_mail_clicked();

    void on_boutton_settings_exporter_clicked();


    void on_btn_add_4_clicked();

    void on_pushButton_clicked();

    void on_lineEdit_chat_returnPressed();

    void on_returnfromchat_clicked();

    void on_pushButton_2_clicked();

    void on_opplus_clicked();

    void on_opmoins_clicked();

    void on_opetoile_clicked();

    void on_opsur_clicked();
    void printplante(QPrinter *);
    void printproduitv(QPrinter *);

    void on_print_plante_clicked();

    void on_print_pr_vg_clicked();

    void on_tableViewVehilcule_activated(const QModelIndex &index);



    void on_tableViewEquipement_activated(const QModelIndex &index);

    void on_input_recherche_vehicule_textChanged(const QString &arg1);

    void on_input_recherche_eq_textChanged(const QString &arg1);



    void on_recherche_n_textChanged(const QString &arg1);

    void on_pushButton_retourstatv_clicked();

    void on_pushButton_retourstate_clicked();

    void on_statistique_vehilcule_clicked();

    void on_statistique_equipement_clicked();

    void on_pushButton_execel_clicked();

    void on_pushButton_execel_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_execel_f_clicked();

    void on_pushButton_execel_n_clicked();


    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_login_btn_2_clicked();

    void on_pushButton_imgprofile_clicked();

    void on_pushButton_ajouterf_3_clicked();

    void on_ajouteranim_2_clicked();

    void on_ajouteranim_clicked();

    void on_fs_3_clicked();

    void on_supprimeranim_2_clicked();

    void on_supprimeranim_clicked();

    void on_tableanim_activated(const QModelIndex &index);

    void on_fm_3_clicked();

    void on_pushButton_rechanim_clicked();

    void on_upanim_clicked();

    void on_downanim_clicked();

    void on_nomrecherche_an_textChanged(const QString &arg1);

    void on_pushButton_ajouterf_4_clicked();

    void on_fs_4_clicked();

    void on_supprimerprod_2_clicked();

    void on_ajouterprod_2_clicked();

    void on_ajouterprod_clicked();

    void on_supprimerprod_clicked();

    void on_tableprod_activated(const QModelIndex &index);

    void on_rechprod_clicked();

    void on_downprod_clicked();

    void on_upprod_clicked();

    void on_nomrecherche_proda_textChanged(const QString &arg1);

    void on_tabWidget_4_currentChanged(int index);

    void on_fm_4_clicked();

    void on_pushButton_66_clicked();

    void on_pushButton_65_clicked();

    void on_pushButton_retourstate_3_clicked();

    void on_pushButton_retourstate_2_clicked();

    void on_statistique_vehilcule_3_clicked();

    void on_statistique_vehilcule_2_clicked();

    void on_pushButton_execel_f_3_clicked();

    void on_pushButton_execel_f_2_clicked();

    void on_pushButton_execel_f_5_clicked();

    void on_pushButton_execel_f_4_clicked();

    void on_pushButton_execel_f_6_clicked();

    void on_pushButton_execel_f_7_clicked();

    void on_pushButton_67_clicked();

    void on_stats_2_clicked();

    void on_pushButton_retourstate_4_clicked();

    void on_pushButton_15_clicked();

private:
    Email createEmail();
    Email createEmail_2();
    Email createEmail_3();
private:
    Ui::MainWindow *ui;
    fournisseur tmpfournisseur;
    nourriture tmpnourriture;
    QSystemTrayIcon *mSystemTrayIcon ;
    QMediaPlayer * player;
  //QMediaPlayer *play;
    QStandardItemModel * m_playListModel ;  // Playlist data model to display
  //QMediaPlayer * m_player ;  // Track player
    QMediaPlaylist * m_playlist ;  // Player playlist
    QTimer *timereal,*timerealll ;
    QElapsedTimer timer;
    SMTPClient *client_;
    avis_fournisseur tmpavisf;
    QString file_path_;
    QTranslator translatorEn;
    int mute ;
    profil tmpprofil;
    ouvrier tmpouvrier;
    plante tmpplante;
    produitv tmpproduitv;
    equipement tmpequipement;
    vehicule tmpvehicule;
    //
    QString mail;
    QString mdp;
    QString exporter;
    //
    QString idp,nom;
   // int nb_chat,,nb_p;
    int   aze;
    Animal tmpanimal;
    Produit tmpprod;

protected:
    void changeEvent(QEvent*);
};
#endif // MAINWINDOW_H
