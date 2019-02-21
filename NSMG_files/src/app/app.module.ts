import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { FormsModule } from '@angular/forms';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { HeaderComponent } from './header/header.component';
import { CharacterListComponent } from './character-list/character-list.component';
import { MainComponent } from './main/main.component';
import { CharacterAnimationComponent } from './character-animation/character-animation.component';
import { CharacterProfileComponent } from './character-profile/character-profile.component';
import { SidebarComponent } from './header/sidebar/sidebar.component';

@NgModule({
  declarations: [
    AppComponent,
    HeaderComponent,
    CharacterListComponent,
    MainComponent,
    CharacterAnimationComponent,
    CharacterProfileComponent,
    SidebarComponent
  ],
  imports: [
    BrowserModule,
    FormsModule,
    AppRoutingModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
