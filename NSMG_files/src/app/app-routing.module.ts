import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';
import { CharacterListComponent } from './character-list/character-list.component';
import { MainComponent } from './main/main.component';
import { CharacterProfileComponent } from './character-profile/character-profile.component';
import { CharacterAnimationComponent } from './character-animation/character-animation.component';

const routes: Routes = [
  { path: 'characterList', component: CharacterListComponent },
  { path: 'characterProfile', component: CharacterProfileComponent },
  { path: 'characterAnimation', component: CharacterAnimationComponent },
  { path: '', component: MainComponent }
  // { path: '', redirectTo: 'main', pathMatch: 'full' }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})

export class AppRoutingModule {}
