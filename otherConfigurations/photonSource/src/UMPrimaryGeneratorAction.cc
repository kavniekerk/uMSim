#include "UMPrimaryGeneratorAction.hh"
#include "UMDetectorConstruction.hh"

#include "Randomize.hh"

#include "globals.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"

#include "UMConfig.hh"

#include <fstream>
#include <iostream>

UMPrimaryGeneratorAction::UMPrimaryGeneratorAction(): G4VUserPrimaryGeneratorAction(),
particleGun(0)
{
    
    UMConfig config;
    
    G4int nparticle=1;
    particleGun=new G4ParticleGun(nparticle);		// particles per event
    G4ParticleTable* particleTable=G4ParticleTable::GetParticleTable();
    G4String particleName;
    beamParticle = particleTable->FindParticle(particleName="gamma");
    
    // define the energy of the beam
    
    beamEnergy = 0;//config.beamEnergy;
    
    // G4cout << "---> Beam energy : " << config.beamEnergy << G4endl;
    
    // define the distance of the particle gun
    // wrt to the center of the world
    // assuming that the gun is at the center of the detector
    // in a vertical distance of particleGun_Xdistance:
    particleGun_Xdistance = config.particleGun_Xdistance;//2300000.*um;
    particleGun_Ydistance = config.particleGun_Ydistance;//0.0*um;
    particleGun_Z_distance = config.particleGun_Z_distance; //0.0*um;
    
    
    // detector construction related
    pcb_total_thickness = config.pcb_total_thickness; //2000.*um;
    frame_total_thickness = config.frame_total_thickness;//20000*um;
    detector_half_width = config.detector_half_width;//100000.*um;
    detector_total_thickness = config.pcb_halfX+2.*config.frame_halfX+2.*config.pcb_halfX; //pcb_total_thickness+frame_total_thickness; // equals to the width of PCB+Aluminum frame
    
    
    
}

UMPrimaryGeneratorAction::~UMPrimaryGeneratorAction()
{
    delete particleGun;
}

void UMPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    
    particleGun_Xdistance = detector_total_thickness+100.*um;//2300000.*um;
    particleGun_Ydistance = 0.0*um;
    particleGun_Z_distance = 0.0*um;
    
    
    
    particleGun->SetParticlePosition(G4ThreeVector(particleGun_Xdistance, particleGun_Ydistance, particleGun_Z_distance));//new , palio itan 2.05
    particleGun->SetParticleDefinition(beamParticle);
    
    
    // this is to get the Fe-55 source gamma energies
    //G4double anumber =G4UniformRand();
    //if (anumber<=0.01){
    //    beamEnergy = 0.64*keV;
    //    particleGun->SetParticleEnergy(0.64*keV);
    //    
    //}else if ((anumber>0.01)&&(anumber<=0.3)){
    //    beamEnergy = 5.888*keV;
    //    particleGun->SetParticleEnergy(5.888*keV);
    //    
    //}else if ((anumber>0.3)&&(anumber<=0.88)){
    //    beamEnergy = 5.899*keV;
    //    particleGun->SetParticleEnergy(5.899*keV);
    //    
    //}else if (anumber>0.88){
    //    beamEnergy = 6.49*keV;
    //    particleGun->SetParticleEnergy(6.49*keV);
    // }
    

    // This is for Cd-109
    /*G4double anumber =G4UniformRand();
    if (anumber<=0.096){
        beamEnergy = 2.98*keV;
        particleGun->SetParticleEnergy(2.98*keV);

    }else if ((anumber>0.096)&&(anumber<=0.345)){
        beamEnergy = 21.990*keV;
        particleGun->SetParticleEnergy(21.990*keV);

    }else if ((anumber>0.345)&&(anumber<=0.817)){
        beamEnergy = 22.163*keV;
        particleGun->SetParticleEnergy(22.163*keV);

    }else if ((anumber>0.817)&&(anumber<=0.969)){
        beamEnergy = 24.9*keV;
        particleGun->SetParticleEnergy(24.9*keV);
    }
    else if (anumber>0.969){
	beamEnergy = 88.034*keV;
	particleGun->SetParticleEnergy(88.034*keV);
    }
*/
// Both Fe + Cd
    G4double anumber =G4UniformRand();
    if (anumber<=0.048){
        beamEnergy = 2.98*keV;
        particleGun->SetParticleEnergy(2.98*keV);

    }else if ((anumber>0.048)&&(anumber<=0.1725)){
        beamEnergy = 21.990*keV;
        particleGun->SetParticleEnergy(21.990*keV);

    }else if ((anumber>0.1725)&&(anumber<=0.4085)){
        beamEnergy = 22.163*keV;
        particleGun->SetParticleEnergy(22.163*keV);

    }else if ((anumber>0.4085)&&(anumber<=0.4845)){
        beamEnergy = 24.9*keV;
        particleGun->SetParticleEnergy(24.9*keV);
    }
    else if ((anumber>0.4845)&&(anumber<=0.5)){
        beamEnergy = 88.034*keV;
        particleGun->SetParticleEnergy(88.034*keV);
    }
    else if ((anumber>0.50)&&(anumber<=0.505)){
        beamEnergy = 0.64*keV;
        particleGun->SetParticleEnergy(0.64*keV);
    }
    else if ((anumber>0.505)&&(anumber<=0.65)){
        beamEnergy = 5.888*keV;
        particleGun->SetParticleEnergy(5.888*keV);
    }
    else if ((anumber>0.65)&&(anumber<=0.94)){
        beamEnergy = 5.899*keV;
        particleGun->SetParticleEnergy(5.899*keV);
    }
    else if ((anumber>0.94)){
        beamEnergy = 6.49*keV;
        particleGun->SetParticleEnergy(6.49*keV);
    } 


    //G4cout << "---> Beam energy : " << beamEnergy << G4endl;
    //particleGun->SetParticleEnergy(beamEnergy);
    
    // the particle gun is particleGun_Xdistance away from the CENTER of the detector
    // but the maximum opening distance would be aquired if we calculate the angles
    // with respect to the first frame that the particle impacts
    // ===>> to calculate the angles we subtract the half_width of the detector
    G4double bestDistance = particleGun_Xdistance-(detector_total_thickness/2.0);
    //G4cout << "[INFO] PrimaryGenerator : best distance (gun_distance - detector_half_thickness = " << bestDistance << G4endl;
    
    G4double max_height = sqrt((detector_half_width*detector_half_width)+(detector_half_width*detector_half_width));
    
    
    G4double tantheta = (max_height/bestDistance);
    G4double theta = atan(tantheta);
    G4double phi= (G4UniformRand())*2*pi;
    G4double cosrand = 1-(G4UniformRand())*(1-cos(theta));
    
    
    G4double uy= cos(phi) * sqrt(1-cosrand*cosrand);
    G4double uz= sin(phi) * sqrt(1-cosrand*cosrand);
    G4double ux =cosrand;
    
    // set the momentum of X-axis towards the negative direction
    particleGun->SetParticleMomentumDirection(G4ThreeVector(-ux,uy,uz));
    
    
    // now that everything is setup generate an event!
    particleGun->GeneratePrimaryVertex(anEvent);
    
}






//#include "UMPrimaryGeneratorAction.hh"
//#include "UMDetectorConstruction.hh"
//
//#include "Randomize.hh"
//
//#include "globals.hh"
//
//#include "G4PhysicalConstants.hh"
//#include "G4SystemOfUnits.hh"
//#include "G4ParticleDefinition.hh"
//#include "G4ParticleTable.hh"
//#include "G4Event.hh"
//#include "G4ParticleGun.hh"
//
//#include "UMConfig.hh"
//
//#include <fstream>
//#include <iostream>
//
//UMPrimaryGeneratorAction::UMPrimaryGeneratorAction(): G4VUserPrimaryGeneratorAction(),
//particleGun(0)
//{
//    
//    UMConfig config;
//    
//    G4int nparticle=1;
//    particleGun=new G4ParticleGun(nparticle);		// particles per event
//    G4ParticleTable* particleTable=G4ParticleTable::GetParticleTable();
//    G4String particleName;
//    beamParticle = particleTable->FindParticle(particleName=config.beamParticleName);
//    
//    // define the energy of the beam
//    beamEnergy = config.beamEnergy;
//
//	G4cout << "---> Beam energy : " << config.beamEnergy << G4endl;
//    
//    // define the distance of the particle gun
//    // wrt to the center of the world
//    // assuming that the gun is at the center of the detector
//    // in a vertical distance of particleGun_Xdistance:
//    particleGun_Xdistance = config.particleGun_Xdistance;//2300000.*um;
//    particleGun_Ydistance = config.particleGun_Ydistance;//0.0*um;
//    particleGun_Z_distance = config.particleGun_Z_distance; //0.0*um;
//    
//    
//    // detector construction related
//    pcb_total_thickness = config.pcb_total_thickness; //2000.*um;
//    frame_total_thickness = config.frame_total_thickness;//20000*um;
//    detector_half_width = config.detector_half_width;//100000.*um;
//    detector_total_thickness = pcb_total_thickness+frame_total_thickness; // equals to the width of PCB+Aluminum frame
//    
//    
//    
//}
//
//UMPrimaryGeneratorAction::~UMPrimaryGeneratorAction()
//{
//    delete particleGun;
//}
//
//void UMPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
//{
//    
//    //    particleGun_Xdistance = 2300000.*um;
//    //    particleGun_Ydistance = 0.0*um;
//    //    particleGun_Z_distance = 0.0*um;
//    
//
//    
//    particleGun->SetParticlePosition(G4ThreeVector(particleGun_Xdistance, -particleGun_Xdistance, particleGun_Z_distance));//new , palio itan 2.05
//    particleGun->SetParticleDefinition(beamParticle);
//
//    particleGun->SetParticleEnergy(beamEnergy);
//    
//    // the particle gun is particleGun_Xdistance away from the CENTER of the detector
//    // but the maximum opening distance would be aquired if we calculate the angles
//    // with respect to the first frame that the particle impacts
//    // ===>> to calculate the angles we subtract the half_width of the detector
//    G4double bestDistance = particleGun_Xdistance-(detector_total_thickness/2.0);
//    //G4cout << "[INFO] PrimaryGenerator : best distance (gun_distance - detector_half_thickness = " << bestDistance << G4endl;
//    
//    G4double max_height = sqrt((detector_half_width*detector_half_width)+(detector_half_width*detector_half_width));
//    
//    
//    G4double tantheta = (max_height/bestDistance);
//    G4double theta = atan(tantheta);
//    G4double phi= (G4UniformRand())*2*pi;
//    G4double cosrand = 1-(G4UniformRand())*(1-cos(theta));
//    
//    
//    G4double uy= cos(phi) * sqrt(1-cosrand*cosrand);
//    G4double uz= sin(phi) * sqrt(1-cosrand*cosrand);
//    G4double ux =cosrand;
//    
//    // set the momentum of X-axis towards the negative direction
//    particleGun->SetParticleMomentumDirection(G4ThreeVector(-ux,uy,uz).rotateZ(-45.*deg));
//    
//    
//    // now that everything is setup generate an event!
//    particleGun->GeneratePrimaryVertex(anEvent);
//    
//}
//
//
//
//
